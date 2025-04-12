#!/usr/bin/env python3
import os
import shutil
import math
import csv
import re
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import argparse
import json
from collections import defaultdict

class CACTIWrapper:
    def __init__(self, output_dir="NN_Results"):
        self.main_dir = os.getcwd()
        self.output_dir = os.path.join(self.main_dir, output_dir)
        self.results_csv_dir = os.path.join(self.output_dir, "RESULTS_CSV")
        
        # IMC computation configurations
        self.operations = ["bit_serial", "bit_parallel"]
        self.sense_amps = ["CONV", "MRSA", "CESA"]
        self.adder_types = ["blade", "iscas", "new", "dac", "cram"]
        
        # CACTI configuration parameters
        self.tech = 0.028  # 28nm technology
        
        # Precision parameters for calculations
        self.bit_precision = 8  # Default precision in bits
        
        # Memory mapping strategies
        self.mapping_strategies = ["weight_stationary", "output_stationary", "input_stationary"]
        self.current_strategy = "weight_stationary"  # Default strategy
        
        # Cache configuration
        self.fixed_cache_size = None  # If set, use this fixed cache size in bytes, otherwise scale with array size
        self.force_cache_config = True  # If True, force specific cache organization parameters (default=True for backward compatibility)

    def setup_directories(self):
        """Set up the output directories for results"""
        if os.path.exists(self.output_dir):
            shutil.rmtree(self.output_dir)
        
        os.makedirs(self.output_dir)
        os.makedirs(self.results_csv_dir)
        
        # Create subdirectories for each computation type
        for operation in self.operations:
            operation_dir = os.path.join(self.output_dir, operation)
            os.makedirs(operation_dir)
            
            for adder in self.adder_types:
                adder_dir = os.path.join(operation_dir, adder)
                os.makedirs(adder_dir)
                
                for sa in self.sense_amps:
                    sa_dir = os.path.join(adder_dir, sa)
                    os.makedirs(sa_dir)
    
    def modify_config(self, file_path, params):
        """Modify the CACTI configuration file with the specified parameters"""
        with open(file_path, 'r') as file:
            lines = file.readlines()
        
        with open(file_path, 'w') as file:
            for line in lines:
                # Handle cache size - use fixed size if set, otherwise use scaled size
                if "-size (bytes)" in line:
                    cache_size = self.fixed_cache_size if self.fixed_cache_size is not None else params['cache_size']
                    file.write(f"-size (bytes) {cache_size}\n")
                # Handle other standard parameters
                elif "-block size (bytes)" in line:
                    file.write(f"-block size (bytes) {params['block_size']}\n")
                elif "-output/input bus width" in line:
                    file.write(f"-output/input bus width {params['bus_width']}\n")
                elif "-Operation type" in line:
                    file.write(f"-Operation type- \"{params['operation']}\"\n")
                elif "-Adder type" in line:
                    file.write(f"-Adder type - \"{params['adder_type']}\"\n")
                elif "-Sense AMP-" in line:
                    file.write(f"-Sense AMP- \"{params['sense_amp']}\"\n")
                elif "-technology (u)" in line:
                    file.write(f"-technology (u) {self.tech}\n")
                # Handle force cache config flag
                elif "-Force cache config" in line:
                    file.write(f"-Force cache config - \"{str(self.force_cache_config).lower()}\"\n")
                else:
                    file.write(line)
    
    def run_cacti(self, config_file, output_file):
        """Run CACTI with the given configuration file and save output"""
        os.system(f"./cacti -infile {config_file} > {output_file}")
    
    def calculate_memory_requirements(self, workload_params, mapping_strategy):
        """
        Calculate memory requirements for various operations in a neural network
        
        Args:
            workload_params (dict): Parameters for the workload
            mapping_strategy (str): Memory mapping strategy to use
            
        Returns:
            dict: Memory requirements for different components
        """
        memory_reqs = {}
        
        if workload_params['operation_type'] == 'conv':
            input_size = workload_params['input_size']
            kernel_size = workload_params['kernel_size']
            input_channels = workload_params['input_channels']
            output_channels = workload_params['output_channels']
            
            # Calculate output dimensions
            output_size = input_size - kernel_size + 1
            
            # Calculate total elements for weights, inputs, and outputs
            total_weights = kernel_size * kernel_size * input_channels * output_channels
            total_inputs = input_size * input_size * input_channels
            total_outputs = output_size * output_size * output_channels
            
            # Memory requirements depend on mapping strategy
            if mapping_strategy == "weight_stationary":
                # Weights are stationary, inputs and outputs need to be loaded/stored
                memory_reqs['weights'] = total_weights 
                memory_reqs['inputs'] = input_size * input_size * input_channels
                memory_reqs['outputs'] = output_size * output_size * output_channels
                
                # Calculate data reuse factors
                memory_reqs['weight_reuse'] = output_size * output_size
                memory_reqs['input_reuse'] = output_channels
                memory_reqs['output_reuse'] = 1
                
            elif mapping_strategy == "output_stationary":
                # Outputs accumulate in place, weights and inputs need to be loaded
                memory_reqs['weights'] = kernel_size * kernel_size * input_channels
                memory_reqs['inputs'] = input_size * input_size * input_channels
                memory_reqs['outputs'] = output_size * output_size * output_channels
                
                # Calculate data reuse factors
                memory_reqs['weight_reuse'] = 1
                memory_reqs['input_reuse'] = output_channels
                memory_reqs['output_reuse'] = kernel_size * kernel_size * input_channels
                
            elif mapping_strategy == "input_stationary":
                # Inputs are stationary, weights and outputs need to be loaded/stored
                memory_reqs['weights'] = kernel_size * kernel_size * input_channels * output_channels
                memory_reqs['inputs'] = input_size * input_size * input_channels
                memory_reqs['outputs'] = output_size * output_size
                
                # Calculate data reuse factors
                memory_reqs['weight_reuse'] = 1
                memory_reqs['input_reuse'] = kernel_size * kernel_size * output_channels
                memory_reqs['output_reuse'] = input_channels
                
        elif workload_params['operation_type'] == 'matmul':
            M = workload_params['M']
            N = workload_params['N']
            K = workload_params['K']
            
            # For matrix multiplication C(M,N) = A(M,K) * B(K,N)
            memory_reqs['weights'] = K * N  # Matrix B
            memory_reqs['inputs'] = M * K   # Matrix A
            memory_reqs['outputs'] = M * N  # Matrix C
            
            if mapping_strategy == "weight_stationary":
                memory_reqs['weight_reuse'] = M
                memory_reqs['input_reuse'] = N
                memory_reqs['output_reuse'] = 1
            elif mapping_strategy == "output_stationary":
                memory_reqs['weight_reuse'] = 1
                memory_reqs['input_reuse'] = 1
                memory_reqs['output_reuse'] = K
            elif mapping_strategy == "input_stationary":
                memory_reqs['weight_reuse'] = N
                memory_reqs['input_reuse'] = 1
                memory_reqs['output_reuse'] = K
                
        # Scale by bit precision (convert to bytes)
        for key in ['weights', 'inputs', 'outputs']:
            memory_reqs[f'{key}_bytes'] = math.ceil(memory_reqs[key] * self.bit_precision / 8)
            
        return memory_reqs
    
    def parse_network_layer(self, layer_type, layer_params, mapping_strategy=None):
        """
        Parse a neural network layer into CACTI parameters
        
        Args:
            layer_type (str): Type of layer ('conv', 'fc', 'pool', etc.)
            layer_params (dict): Parameters specific to the layer type
            mapping_strategy (str): Memory mapping strategy to use
            
        Returns:
            list: List of configurations to test
        """
        configs = []
        
        if mapping_strategy is None:
            mapping_strategy = self.current_strategy
            
        # Set up workload parameters based on layer type
        workload_params = {'operation_type': layer_type}
        workload_params.update(layer_params)
        
        # Calculate memory requirements
        memory_reqs = self.calculate_memory_requirements(workload_params, mapping_strategy)
        
        # Try different memory configurations
        # Different array sizes to evaluate
        array_sizes = [64, 128, 256, 512, 1024]
        
        for array_size in array_sizes:
            rows = array_size
            cols = array_size
            
            # Calculate required memory size in bytes
            cache_size = (rows * cols) // 8
            block_size = cols // 8
            bus_width = cols
            
            for operation in self.operations:
                for adder_type in self.adder_types:
                    for sense_amp in self.sense_amps:
                        config = {
                            'cache_size': cache_size,
                            'block_size': block_size,
                            'bus_width': bus_width, 
                            'rows': rows,
                            'cols': cols,
                            'operation': operation,
                            'adder_type': adder_type,
                            'sense_amp': sense_amp,
                            'mapping_strategy': mapping_strategy,
                            'layer_type': layer_type
                        }
                        
                        # Add layer-specific parameters
                        config.update(layer_params)
                        
                        # Add memory requirements
                        config.update(memory_reqs)
                        
                        configs.append(config)
        
        return configs
    
    def run_layer_analysis(self, layer_type, layer_params, mapping_strategy=None):
        """Run analysis for a neural network layer"""
        if layer_type == 'conv':
            print(f"Analyzing convolutional layer with input size {layer_params['input_size']}x{layer_params['input_size']}, "
                  f"kernel {layer_params['kernel_size']}x{layer_params['kernel_size']}, "
                  f"input channels {layer_params['input_channels']}, output channels {layer_params['output_channels']}")
        elif layer_type == 'matmul':
            print(f"Analyzing matrix multiplication with dimensions M={layer_params['M']}, N={layer_params['N']}, K={layer_params['K']}")
        
        # Setup directories
        self.setup_directories()
        
        # Get configurations to test
        configs = self.parse_network_layer(layer_type, layer_params, mapping_strategy)
        
        # Create temp config file
        temp_config = "temp_config.cfg"
        shutil.copy("cache_bs_bp.cfg", temp_config)
        
        results = []
        
        # Run CACTI for each configuration
        for i, config in enumerate(configs):
            print(f"Running configuration {i+1}/{len(configs)}: {config['operation']}, {config['adder_type']}, {config['sense_amp']}")
            
            # Modify config file
            self.modify_config(temp_config, config)
            
            # Define output file path
            output_file = os.path.join(
                self.output_dir,
                config['operation'],
                config['adder_type'],
                config['sense_amp'],
                f"array_{config['rows']}x{config['cols']}.txt"
            )
            
            # Run CACTI
            self.run_cacti(temp_config, output_file)
            
            # Extract results from output file
            result = self.extract_results(output_file, config)
            
            # If valid results were obtained
            if result.get('access_time_ns') is not None:
                # Calculate layer-specific performance metrics
                result = self.calculate_layer_performance(result)
                results.append(result)
            else:
                print(f"Warning: Invalid results for configuration {i+1}, skipping...")
        
        # Cleanup temp file
        os.remove(temp_config)
        
        # Create DataFrame from results
        results_df = pd.DataFrame(results) if results else pd.DataFrame()
        
        # Save results to CSV if we have any
        if not results_df.empty:
            results_csv_path = os.path.join(self.results_csv_dir, f"{layer_type}_results.csv")
            results_df.to_csv(results_csv_path, index=False)
            
            # Generate summary plots if we have valid results
            self.generate_summary_plots(results_df, layer_type)
        else:
            print("Warning: No valid results obtained from any configuration.")
        
        # Find the best configuration (handles empty dataframes)
        best_config = self.find_optimal_configuration(results_df)
        
        # Save recommendations
        self.save_recommendations(best_config, layer_type)
        
        return results_df, best_config
    
    def calculate_layer_performance(self, result):
        """
        Calculate layer-specific performance metrics based on the CACTI results
        
        Args:
            result (dict): Dictionary of CACTI results for a configuration
            
        Returns:
            dict: Updated results with layer-specific performance metrics
        """
        layer_type = result['layer_type']
        mapping_strategy = result['mapping_strategy']
        
        # Calculate total operations
        if layer_type == 'conv':
            input_size = result['input_size']
            kernel_size = result['kernel_size']
            input_channels = result['input_channels']
            output_channels = result['output_channels']
            
            output_size = input_size - kernel_size + 1
            
            # Each output point requires kernel_size^2 * input_channels MACs
            macs_per_output = kernel_size * kernel_size * input_channels
            total_macs = output_size * output_size * output_channels * macs_per_output
            
            # Each MAC is 1 mult + 1 add
            total_mults = total_macs
            total_adds = total_macs
            
            # Memory accesses depend on mapping strategy
            if mapping_strategy == "weight_stationary":
                # Weights loaded once, inputs and outputs accessed per computation
                weight_accesses = kernel_size * kernel_size * input_channels * output_channels
                input_accesses = input_size * input_size * input_channels * output_channels / result['input_reuse']
                output_accesses = output_size * output_size * output_channels * 2  # Read and write
                
            elif mapping_strategy == "output_stationary":
                # Weights and inputs accessed per computation, outputs accumulated in place
                weight_accesses = kernel_size * kernel_size * input_channels * output_channels
                input_accesses = input_size * input_size * input_channels * output_channels / result['input_reuse']
                output_accesses = output_size * output_size * output_channels * 2  # Initial read and final write
                
            elif mapping_strategy == "input_stationary":
                # Inputs loaded once, weights and outputs accessed per computation
                input_accesses = input_size * input_size * input_channels
                weight_accesses = kernel_size * kernel_size * input_channels * output_channels
                output_accesses = output_size * output_size * output_channels * 2  # Read and write
                
        elif layer_type == 'matmul':
            M = result['M']
            N = result['N']
            K = result['K']
            
            # For matrix multiplication C(M,N) = A(M,K) * B(K,N)
            total_macs = M * N * K
            total_mults = total_macs
            total_adds = total_macs
            
            # Memory accesses depend on mapping strategy
            if mapping_strategy == "weight_stationary":
                weight_accesses = K * N  # Matrix B loaded once
                input_accesses = M * K * N  # Matrix A accessed N times
                output_accesses = M * N * 2  # Matrix C read and write
                
            elif mapping_strategy == "output_stationary":
                weight_accesses = K * N * M  # Matrix B accessed M times
                input_accesses = M * K  # Matrix A loaded once
                output_accesses = M * N * 2  # Initial read and final write
                
            elif mapping_strategy == "input_stationary":
                input_accesses = M * K  # Matrix A loaded once
                weight_accesses = K * N * M  # Matrix B accessed M times
                output_accesses = M * N * 2  # Read and write
        
        # Calculate performance metrics based on operation type
        if result['operation'] == 'bit_serial':
            # For bit-serial, each n-bit operation takes n cycles
            cycles_per_mult = self.bit_precision * self.bit_precision
            cycles_per_add = self.bit_precision
            
            # Total execution time
            mult_time = result.get('mult_delay_ns', 0) * total_mults
            add_time = result.get('add_delay_ns', 0) * total_adds
            
            # Total energy
            mult_energy = result.get('mult_energy_nJ', 0) * total_mults
            add_energy = result.get('add_energy_nJ', 0) * total_adds
            
        else:  # bit-parallel
            # For bit-parallel, each operation takes 1 cycle
            cycles_per_mult = 1
            cycles_per_add = 1
            
            # Total execution time - assume multipliers have similar delay to adders
            mult_time = result.get('add_delay_ns', 0) * total_mults  # Approximate
            add_time = result.get('add_delay_ns', 0) * total_adds
            
            # Total energy
            mult_energy = result.get('add_energy_nJ', 0) * total_mults * 3  # Approximate
            add_energy = result.get('add_energy_nJ', 0) * total_adds
        
        # Memory access time and energy
        memory_access_time = result.get('access_time_ns', 0) * (weight_accesses + input_accesses + output_accesses)
        memory_access_energy = result.get('dynamic_energy_nJ', 0) * (weight_accesses + input_accesses + output_accesses)
        
        # Total time and energy
        total_time = mult_time + add_time + memory_access_time
        total_energy = mult_energy + add_energy + memory_access_energy
        
        # Throughput
        throughput_gops = total_macs / total_time  # GOPS
        
        # Energy efficiency
        energy_efficiency = total_macs / total_energy  # GOPS/W
        
        # Add to results
        result.update({
            'total_macs': total_macs,
            'total_mults': total_mults,
            'total_adds': total_adds,
            'weight_accesses': weight_accesses,
            'input_accesses': input_accesses,
            'output_accesses': output_accesses,
            'total_memory_accesses': weight_accesses + input_accesses + output_accesses,
            'cycles_per_mult': cycles_per_mult,
            'cycles_per_add': cycles_per_add,
            'mult_time_ns': mult_time,
            'add_time_ns': add_time,
            'memory_access_time_ns': memory_access_time,
            'total_time_ns': total_time,
            'mult_energy_nJ_total': mult_energy,
            'add_energy_nJ_total': add_energy,
            'memory_access_energy_nJ': memory_access_energy,
            'total_energy_nJ': total_energy,
            'throughput_gops': throughput_gops,
            'energy_efficiency_gops_per_w': energy_efficiency
        })
        
        return result
    
    def extract_results(self, output_file, config):
        """Extract key results from CACTI output file"""
        result = config.copy()
        
        with open(output_file, 'r') as file:
            content = file.read()
            
            # Extract key metrics
            # Access time
            access_time_match = re.search(r'Access time \(ns\):\s*([\d\.]+)', content)
            if access_time_match:
                result['access_time_ns'] = float(access_time_match.group(1))
            
            # Dynamic energy
            energy_match = re.search(r'Total dynamic read energy per access \(nJ\):\s*([\d\.]+)', content)
            if energy_match:
                result['dynamic_energy_nJ'] = float(energy_match.group(1))
            
            # For bit-serial operations
            if config['operation'] == 'bit_serial':
                # Addition delay
                add_delay_match = re.search(r'Bit_serial_delay_for_Nbits_addtion \(ns\):\s*([\d\.]+)', content)
                if add_delay_match:
                    result['add_delay_ns'] = float(add_delay_match.group(1))
                
                # Multiplication delay
                mult_delay_match = re.search(r'Bit_serial_delay_for_Nbits_multiplication \(ns\):\s*([\d\.]+)', content)
                if mult_delay_match:
                    result['mult_delay_ns'] = float(mult_delay_match.group(1))
                
                # Addition energy
                add_energy_match = re.search(r'Bit_serial_energy_for_Nbits_addtion \(nJ\):\s*([\d\.]+)', content)
                if add_energy_match:
                    result['add_energy_nJ'] = float(add_energy_match.group(1))
                
                # Multiplication energy
                mult_energy_match = re.search(r'Bit_serial_energy_for_Nbits_multiplication \(nJ\):\s*([\d\.]+)', content)
                if mult_energy_match:
                    result['mult_energy_nJ'] = float(mult_energy_match.group(1))
            
            # For bit-parallel operations
            elif config['operation'] == 'bit_parallel':
                # Add delay and energy
                compute_delay_match = re.search(r'Compute_adder_delay \(ns\):\s*([\d\.]+)', content)
                if compute_delay_match:
                    result['add_delay_ns'] = float(compute_delay_match.group(1))
                
                compute_energy_match = re.search(r'compute adder energy \(nJ\):\s*([\d\.]+)', content)
                if compute_energy_match:
                    result['add_energy_nJ'] = float(compute_energy_match.group(1))
        
        return result
    
    def find_optimal_configuration(self, results_df):
        """
        Find the optimal configuration for a given workload
        
        Args:
            results_df (DataFrame): DataFrame containing all results
            
        Returns:
            dict: A dictionary containing the optimal configurations for different metrics
        """
        best_configs = {}
        
        # Check if results_df is empty
        if results_df.empty:
            print("Warning: No valid results found for the given configuration.")
            # Return empty recommendations
            return {
                'overall_best': {
                    'metric': 'none',
                    'config': {
                        'array_size': 'N/A',
                        'operation': 'N/A',
                        'adder_type': 'N/A',
                        'sense_amp': 'N/A',
                        'mapping_strategy': 'N/A',
                        'throughput_gops': 0,
                        'energy_efficiency_gops_per_w': 0
                    }
                },
                'energy_best': {
                    'metric': 'none',
                    'config': {
                        'array_size': 'N/A',
                        'operation': 'N/A',
                        'adder_type': 'N/A',
                        'sense_amp': 'N/A',
                        'mapping_strategy': 'N/A',
                        'throughput_gops': 0,
                        'energy_efficiency_gops_per_w': 0
                    }
                },
                'latency_best': {
                    'metric': 'none',
                    'config': {
                        'array_size': 'N/A',
                        'operation': 'N/A',
                        'adder_type': 'N/A',
                        'sense_amp': 'N/A',
                        'mapping_strategy': 'N/A',
                        'total_time_ns': 0,
                        'throughput_gops': 0
                    }
                }
            }
        
        # Check if we have any results
        if not results_df.empty:
            # Best throughput configuration
            throughput_idx = results_df['throughput_gops'].idxmax()
            best_configs['throughput'] = results_df.iloc[throughput_idx].to_dict()
            
            # Best energy efficiency configuration
            energy_eff_idx = results_df['energy_efficiency_gops_per_w'].idxmax()
            best_configs['energy_efficiency'] = results_df.iloc[energy_eff_idx].to_dict()
            
            # Best latency configuration (lowest total time)
            latency_idx = results_df['total_time_ns'].idxmin()
            best_configs['latency'] = results_df.iloc[latency_idx].to_dict()
            
            # Best area efficiency (throughput per area)
            results_df['area_efficiency'] = results_df['throughput_gops'] / (results_df['rows'] * results_df['cols'])
            area_eff_idx = results_df['area_efficiency'].idxmax()
            best_configs['area_efficiency'] = results_df.iloc[area_eff_idx].to_dict()
        
        # Skip detailed breakdowns if the dataframe is empty - they're not needed for the basic recommendations
        
        # Prepare a summarized version for recommendations
        recommended = {}
        
        # If there are best configs, prepare them, otherwise use defaults from earlier
        if 'throughput' in best_configs:
            # Overall best
            recommended['overall_best'] = {
                'metric': 'throughput',
                'config': {
                    'array_size': f"{best_configs['throughput']['rows']}x{best_configs['throughput']['cols']}",
                    'operation': best_configs['throughput']['operation'],
                    'adder_type': best_configs['throughput']['adder_type'],
                    'sense_amp': best_configs['throughput']['sense_amp'],
                    'mapping_strategy': best_configs['throughput']['mapping_strategy'],
                    'throughput_gops': best_configs['throughput']['throughput_gops'],
                    'energy_efficiency_gops_per_w': best_configs['throughput']['energy_efficiency_gops_per_w']
                }
            }
            
            # Best for energy efficiency
            recommended['energy_best'] = {
                'metric': 'energy_efficiency',
                'config': {
                    'array_size': f"{best_configs['energy_efficiency']['rows']}x{best_configs['energy_efficiency']['cols']}",
                    'operation': best_configs['energy_efficiency']['operation'],
                    'adder_type': best_configs['energy_efficiency']['adder_type'],
                    'sense_amp': best_configs['energy_efficiency']['sense_amp'],
                    'mapping_strategy': best_configs['energy_efficiency']['mapping_strategy'],
                    'throughput_gops': best_configs['energy_efficiency']['throughput_gops'],
                    'energy_efficiency_gops_per_w': best_configs['energy_efficiency']['energy_efficiency_gops_per_w']
                }
            }
            
            # Best for latency
            recommended['latency_best'] = {
                'metric': 'latency',
                'config': {
                    'array_size': f"{best_configs['latency']['rows']}x{best_configs['latency']['cols']}",
                    'operation': best_configs['latency']['operation'],
                    'adder_type': best_configs['latency']['adder_type'],
                    'sense_amp': best_configs['latency']['sense_amp'],
                    'mapping_strategy': best_configs['latency']['mapping_strategy'],
                    'total_time_ns': best_configs['latency']['total_time_ns'],
                    'throughput_gops': best_configs['latency']['throughput_gops']
                }
            }
        else:
            # Return default values if no valid results found
            recommended['overall_best'] = {
                'metric': 'none',
                'config': {
                    'array_size': 'N/A',
                    'operation': 'N/A',
                    'adder_type': 'N/A',
                    'sense_amp': 'N/A',
                    'mapping_strategy': 'N/A',
                    'throughput_gops': 0,
                    'energy_efficiency_gops_per_w': 0
                }
            }
            recommended['energy_best'] = {
                'metric': 'none',
                'config': {
                    'array_size': 'N/A',
                    'operation': 'N/A',
                    'adder_type': 'N/A',
                    'sense_amp': 'N/A',
                    'mapping_strategy': 'N/A',
                    'throughput_gops': 0,
                    'energy_efficiency_gops_per_w': 0
                }
            }
            recommended['latency_best'] = {
                'metric': 'none',
                'config': {
                    'array_size': 'N/A',
                    'operation': 'N/A',
                    'adder_type': 'N/A',
                    'sense_amp': 'N/A',
                    'mapping_strategy': 'N/A',
                    'total_time_ns': 0,
                    'throughput_gops': 0
                }
            }
        
        return recommended
    
    def save_recommendations(self, recommended, layer_type):
        """
        Save recommendations to a JSON file
        
        Args:
            recommended (dict): Dictionary containing recommendations
            layer_type (str): Type of layer
        """
        json_path = os.path.join(self.results_csv_dir, f"{layer_type}_recommendations.json")
        
        with open(json_path, 'w') as f:
            json.dump(recommended, f, indent=4)
        
        # Also generate a human-readable recommendations file
        txt_path = os.path.join(self.results_csv_dir, f"{layer_type}_recommendations.txt")
        
        with open(txt_path, 'w') as f:
            f.write(f"Recommendations for {layer_type} layer\n")
            f.write("=" * 50 + "\n\n")
            
            # Check if we have valid results or if we're using the default "N/A" values
            if recommended['overall_best']['config']['array_size'] == 'N/A':
                f.write("NO VALID CONFIGURATIONS FOUND\n")
                f.write("-" * 50 + "\n")
                f.write("No valid configurations were found for the given parameters.\n")
                f.write("This may be due to the combination of fixed cache size and array dimensions.\n")
                f.write("Try adjusting the cache size or using different array dimensions.\n\n")
                f.write("NOTE: When using a fixed cache size, not all array dimensions may be compatible.\n")
                return
            
            # Overall best
            f.write("BEST OVERALL CONFIGURATION (THROUGHPUT-OPTIMIZED)\n")
            f.write("-" * 50 + "\n")
            config = recommended['overall_best']['config']
            f.write(f"Array Size: {config['array_size']}\n")
            f.write(f"Operation: {config['operation']}\n")
            f.write(f"Adder Type: {config['adder_type']}\n")
            f.write(f"Sense Amplifier: {config['sense_amp']}\n")
            f.write(f"Mapping Strategy: {config['mapping_strategy']}\n")
            f.write(f"Throughput: {config['throughput_gops']:.2f} GOPS\n")
            f.write(f"Energy Efficiency: {config['energy_efficiency_gops_per_w']:.2f} GOPS/W\n\n")
            
            # Energy best
            f.write("BEST ENERGY-EFFICIENT CONFIGURATION\n")
            f.write("-" * 50 + "\n")
            config = recommended['energy_best']['config']
            f.write(f"Array Size: {config['array_size']}\n")
            f.write(f"Operation: {config['operation']}\n")
            f.write(f"Adder Type: {config['adder_type']}\n")
            f.write(f"Sense Amplifier: {config['sense_amp']}\n")
            f.write(f"Mapping Strategy: {config['mapping_strategy']}\n")
            f.write(f"Throughput: {config['throughput_gops']:.2f} GOPS\n")
            f.write(f"Energy Efficiency: {config['energy_efficiency_gops_per_w']:.2f} GOPS/W\n\n")
            
            # Latency best
            f.write("BEST LATENCY-OPTIMIZED CONFIGURATION\n")
            f.write("-" * 50 + "\n")
            config = recommended['latency_best']['config']
            f.write(f"Array Size: {config['array_size']}\n")
            f.write(f"Operation: {config['operation']}\n")
            f.write(f"Adder Type: {config['adder_type']}\n")
            f.write(f"Sense Amplifier: {config['sense_amp']}\n")
            f.write(f"Mapping Strategy: {config['mapping_strategy']}\n")
            f.write(f"Total Execution Time: {config['total_time_ns']:.2f} ns\n")
            f.write(f"Throughput: {config['throughput_gops']:.2f} GOPS\n\n")
            
            f.write("NOTE: These recommendations assume the given workload and may change for different workloads.\n")
            f.write("Different priorities (throughput, energy, latency) lead to different optimal configurations.\n")
    
    def generate_summary_plots(self, results_df, layer_type):
        """Generate summary plots for the results"""
        # Check if the DataFrame is empty
        if results_df.empty:
            print(f"Warning: No data available to generate plots for {layer_type}")
            return
            
        # Create empty placeholder plots if there are no results
        if len(results_df) == 0:
            # Create placeholder plots with "No Data Available" message
            for plot_type in ["throughput", "energy_efficiency", "mapping_impact"]:
                plt.figure(figsize=(12, 6))
                plt.text(0.5, 0.5, "No data available", ha='center', va='center', fontsize=20)
                plt.title(f"{plot_type.replace('_', ' ').title()} - No Data Available")
                plt.savefig(os.path.join(self.results_csv_dir, f"{layer_type}_{plot_type}.png"))
                plt.close()
            return
        
        # Throughput vs Array Size plot
        plt.figure(figsize=(12, 6))
        for operation in self.operations:
            operation_df = results_df[results_df['operation'] == operation]
            if not operation_df.empty:
                avg_throughput = operation_df.groupby('rows')['throughput_gops'].mean()
                plt.plot(avg_throughput.index, avg_throughput.values, marker='o', label=operation)
        
        plt.title(f"Throughput vs Array Size ({layer_type})")
        plt.xlabel("Array Size")
        plt.ylabel("Throughput (GOPS)")
        plt.xscale('log', base=2)
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(self.results_csv_dir, f"{layer_type}_throughput.png"))
        plt.close()
        
        # Energy Efficiency vs Array Size plot
        plt.figure(figsize=(12, 6))
        for operation in self.operations:
            operation_df = results_df[results_df['operation'] == operation]
            if not operation_df.empty:
                avg_energy_eff = operation_df.groupby('rows')['energy_efficiency_gops_per_w'].mean()
                plt.plot(avg_energy_eff.index, avg_energy_eff.values, marker='o', label=operation)
        
        plt.title(f"Energy Efficiency vs Array Size ({layer_type})")
        plt.xlabel("Array Size")
        plt.ylabel("Energy Efficiency (GOPS/W)")
        plt.xscale('log', base=2)
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(self.results_csv_dir, f"{layer_type}_energy_efficiency.png"))
        plt.close()
        
        # Different memory mapping strategies comparison
        if 'mapping_strategy' in results_df.columns and len(results_df['mapping_strategy'].unique()) > 0:
            plt.figure(figsize=(12, 6))
            for mapping in results_df['mapping_strategy'].unique():
                mapping_df = results_df[results_df['mapping_strategy'] == mapping]
                if not mapping_df.empty:
                    avg_throughput = mapping_df.groupby('rows')['throughput_gops'].mean()
                    plt.plot(avg_throughput.index, avg_throughput.values, marker='o', label=mapping)
            
            plt.title(f"Impact of Memory Mapping Strategy on Throughput ({layer_type})")
            plt.xlabel("Array Size")
            plt.ylabel("Throughput (GOPS)")
            plt.xscale('log', base=2)
            plt.grid(True)
            plt.legend()
            plt.savefig(os.path.join(self.results_csv_dir, f"{layer_type}_mapping_impact.png"))
            plt.close()
    
    def run_resnet_analysis(self, input_size, kernel_size, input_channels, output_channels):
        """Wrapper for run_layer_analysis for ResNet layers"""
        layer_params = {
            'input_size': input_size,
            'kernel_size': kernel_size,
            'input_channels': input_channels,
            'output_channels': output_channels
        }
        
        # Run analysis for different mapping strategies
        results = []
        for strategy in self.mapping_strategies:
            print(f"\nAnalyzing with {strategy} mapping strategy:")
            result, best_config = self.run_layer_analysis('conv', layer_params, strategy)
            results.append((result, best_config))
        
        # Compare different mapping strategies
        self.compare_mapping_strategies(results, 'conv')
        
        return results[-1]  # Return results for last strategy
    
    def run_transformer_analysis(self, seq_len, hidden_size, num_heads):
        """Run analysis for a transformer layer"""
        # For transformer, we primarily care about matrix multiplications
        # for attention mechanism and feed-forward network
        
        # Attention projection matrices: Q, K, V projections
        qkv_params = {
            'M': seq_len,              # Sequence length
            'N': hidden_size // num_heads,  # Per-head dimension
            'K': hidden_size           # Hidden dimension
        }
        
        # Feed-forward network
        ffn_params = {
            'M': seq_len,             # Sequence length
            'N': hidden_size * 4,     # Intermediate dimension (usually 4x hidden)
            'K': hidden_size          # Hidden dimension
        }
        
        # Run analysis for different parts
        print("\nAnalyzing transformer attention mechanism:")
        attn_results, attn_best = self.run_layer_analysis('matmul', qkv_params)
        
        print("\nAnalyzing transformer feed-forward network:")
        ffn_results, ffn_best = self.run_layer_analysis('matmul', ffn_params)
        
        # Combine and save overall recommendations
        combined_recommendations = {
            'attention': attn_best,
            'feed_forward': ffn_best,
            'overall': {}  # Will be filled below
        }
        
        # Determine overall best configuration
        # Prioritize the config that works best for the larger/more intensive operation
        if ffn_params['M'] * ffn_params['N'] * ffn_params['K'] > qkv_params['M'] * qkv_params['N'] * qkv_params['K']:
            combined_recommendations['overall'] = ffn_best
        else:
            combined_recommendations['overall'] = attn_best
        
        # Save combined recommendations
        with open(os.path.join(self.results_csv_dir, "transformer_recommendations.json"), 'w') as f:
            json.dump(combined_recommendations, f, indent=4)
        
        return attn_results, ffn_results, combined_recommendations
    
    def compare_mapping_strategies(self, strategy_results, layer_type):
        """
        Compare different memory mapping strategies
        
        Args:
            strategy_results (list): List of (result_df, best_config) tuples for each strategy
            layer_type (str): Type of layer
        """
        # Extract strategy names and results
        strategies = self.mapping_strategies[:len(strategy_results)]
        throughputs = []
        energy_efficiencies = []
        
        has_valid_results = False
        
        for i, (result_df, _) in enumerate(strategy_results):
            # Check if this strategy has valid results
            if not result_df.empty:
                has_valid_results = True
                # Average throughput and energy efficiency across array sizes
                avg_throughput = result_df['throughput_gops'].mean()
                avg_energy_eff = result_df['energy_efficiency_gops_per_w'].mean()
            else:
                # No valid results for this strategy
                avg_throughput = 0
                avg_energy_eff = 0
                
            throughputs.append(avg_throughput)
            energy_efficiencies.append(avg_energy_eff)
        
        # Save comparison to file even if there are no valid results
        comparison = {
            'strategies': strategies,
            'avg_throughput': throughputs,
            'avg_energy_efficiency': energy_efficiencies,
            'has_valid_results': has_valid_results
        }
        
        json_path = os.path.join(self.results_csv_dir, f"{layer_type}_strategy_comparison.json")
        with open(json_path, 'w') as f:
            json.dump(comparison, f, indent=4)
            
        # If there are no valid results, create a placeholder plot
        if not has_valid_results:
            plt.figure(figsize=(12, 6))
            plt.text(0.5, 0.5, "No valid data available for comparison", ha='center', va='center', fontsize=20)
            plt.title(f"Strategy Comparison - No Valid Data")
            plt.savefig(os.path.join(self.results_csv_dir, f"{layer_type}_strategy_comparison.png"))
            plt.close()
            return
        
        # Plot comparison
        plt.figure(figsize=(12, 6))
        x = range(len(strategies))
        
        plt.subplot(1, 2, 1)
        plt.bar(x, throughputs)
        plt.xticks(x, strategies, rotation=45)
        plt.title(f"Average Throughput by Mapping Strategy ({layer_type})")
        plt.ylabel("Throughput (GOPS)")
        plt.grid(axis='y')
        
        plt.subplot(1, 2, 2)
        plt.bar(x, energy_efficiencies)
        plt.xticks(x, strategies, rotation=45)
        plt.title(f"Average Energy Efficiency by Mapping Strategy ({layer_type})")
        plt.ylabel("Energy Efficiency (GOPS/W)")
        plt.grid(axis='y')
        
        plt.tight_layout()
        plt.savefig(os.path.join(self.results_csv_dir, f"{layer_type}_strategy_comparison.png"))
        plt.close()

def main():
    parser = argparse.ArgumentParser(description='CACTI Neural Network Analysis Tool')
    parser.add_argument('--model', type=str, default='resnet', help='Neural network model to analyze (resnet, transformer)')
    parser.add_argument('--input_size', type=int, default=56, help='Input feature map size (default: 56)')
    parser.add_argument('--kernel_size', type=int, default=3, help='Kernel size (default: 3)')
    parser.add_argument('--input_channels', type=int, default=64, help='Number of input channels (default: 64)')
    parser.add_argument('--output_channels', type=int, default=64, help='Number of output channels (default: 64)')
    parser.add_argument('--seq_len', type=int, default=512, help='Sequence length for transformer models (default: 512)')
    parser.add_argument('--hidden_size', type=int, default=768, help='Hidden dimension for transformer models (default: 768)')
    parser.add_argument('--num_heads', type=int, default=12, help='Number of attention heads for transformer models (default: 12)')
    parser.add_argument('--mapping', type=str, default='weight_stationary', help='Memory mapping strategy (weight_stationary, output_stationary, input_stationary)')
    parser.add_argument('--output_dir', type=str, default='NN_Results', help='Output directory for results')
    parser.add_argument('--bit_precision', type=int, default=8, help='Bit precision for calculations (default: 8)')
    
    # New arguments for cache configuration
    parser.add_argument('--fixed_cache_size', type=int, help='Fixed cache size in bytes (e.g. 65536 for 64KB). If not specified, cache size will scale with array dimensions.')
    parser.add_argument('--no_force_config', action='store_true', help='Allow CACTI to determine optimal cache organization instead of forcing specific parameters')
    
    args = parser.parse_args()
    
    wrapper = CACTIWrapper(output_dir=args.output_dir)
    wrapper.bit_precision = args.bit_precision
    wrapper.current_strategy = args.mapping
    
    # Set up new configuration options
    if args.fixed_cache_size is not None:
        wrapper.fixed_cache_size = args.fixed_cache_size
        print(f"Using fixed cache size: {args.fixed_cache_size} bytes")
    
    if args.no_force_config:
        wrapper.force_cache_config = False
        print("Allowing CACTI to determine optimal cache organization")
    
    if args.model.lower() == 'resnet':
        results, best_config = wrapper.run_resnet_analysis(
            args.input_size, 
            args.kernel_size, 
            args.input_channels, 
            args.output_channels
        )
        print("\nAnalysis complete. Best configuration for ResNet layer:")
        print(f"Array Size: {best_config['overall_best']['config']['array_size']}")
        print(f"Operation: {best_config['overall_best']['config']['operation']}")
        print(f"Adder Type: {best_config['overall_best']['config']['adder_type']}")
        print(f"Sense Amp: {best_config['overall_best']['config']['sense_amp']}")
        print(f"Mapping Strategy: {best_config['overall_best']['config']['mapping_strategy']}")
        print(f"Throughput: {best_config['overall_best']['config']['throughput_gops']:.2f} GOPS")
        
    elif args.model.lower() == 'transformer':
        attn_results, ffn_results, combined_recommendations = wrapper.run_transformer_analysis(
            args.seq_len,
            args.hidden_size,
            args.num_heads
        )
        print("\nAnalysis complete. Best configuration for Transformer:")
        print(f"Array Size: {combined_recommendations['overall']['overall_best']['config']['array_size']}")
        print(f"Operation: {combined_recommendations['overall']['overall_best']['config']['operation']}")
        print(f"Adder Type: {combined_recommendations['overall']['overall_best']['config']['adder_type']}")
        print(f"Sense Amp: {combined_recommendations['overall']['overall_best']['config']['sense_amp']}")
        print(f"Mapping Strategy: {combined_recommendations['overall']['overall_best']['config']['mapping_strategy']}")
        
    else:
        print(f"Unsupported model: {args.model}. Please choose 'resnet' or 'transformer'.")
        return
    
    print(f"Detailed results saved to: {args.output_dir}")

if __name__ == "__main__":
    main()