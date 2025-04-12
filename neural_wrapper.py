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
                if "-size (bytes)" in line:
                    file.write(f"-size (bytes) {params['cache_size']}\n")
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
                else:
                    file.write(line)
    
    def run_cacti(self, config_file, output_file):
        """Run CACTI with the given configuration file and save output"""
        os.system(f"./cacti -infile {config_file} > {output_file}")
    
    def parse_resnet_conv_layer(self, input_size, kernel_size, input_channels, output_channels):
        """
        Parse a ResNet convolutional layer into CACTI parameters
        
        Args:
            input_size (int): Size of input feature map (assumes square)
            kernel_size (int): Size of convolutional kernel (assumes square)
            input_channels (int): Number of input channels
            output_channels (int): Number of output channels
            
        Returns:
            dict: Dictionary of configurations to test
        """
        configs = []
        
        # Calculate memory sizes needed for the convolution operation
        # For each output point, we need kernel_size × kernel_size × input_channels values
        # Total input memory required for a single computation
        elements_per_conv = kernel_size * kernel_size * input_channels
        
        # Try different memory configurations
        # Different array sizes to evaluate
        array_sizes = [64, 128, 256, 512, 1024]
        
        for array_size in array_sizes:
            rows = array_size
            cols = array_size
            
            # Calculate required memory size in bytes (8 bits per value)
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
                            'input_size': input_size,
                            'kernel_size': kernel_size,
                            'input_channels': input_channels,
                            'output_channels': output_channels
                        }
                        configs.append(config)
        
        return configs
    
    def run_resnet_analysis(self, input_size, kernel_size, input_channels, output_channels):
        """Run analysis for a ResNet convolutional layer"""
        print(f"Analyzing ResNet layer with input size {input_size}x{input_size}, "
              f"kernel {kernel_size}x{kernel_size}, "
              f"input channels {input_channels}, output channels {output_channels}")
        
        # Setup directories
        self.setup_directories()
        
        # Get configurations to test
        configs = self.parse_resnet_conv_layer(input_size, kernel_size, input_channels, output_channels)
        
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
            results.append(result)
        
        # Cleanup temp file
        os.remove(temp_config)
        
        # Save results to CSV
        results_df = pd.DataFrame(results)
        results_df.to_csv(os.path.join(self.results_csv_dir, "resnet_conv_results.csv"), index=False)
        
        # Generate summary plots
        self.generate_summary_plots(results_df)
        
        return results_df
    
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
    
    def generate_summary_plots(self, results_df):
        """Generate summary plots for the results"""
        plt.figure(figsize=(12, 8))
        
        # Group results by operation, adder_type, and sense_amp
        for operation in self.operations:
            operation_df = results_df[results_df['operation'] == operation]
            
            plt.figure(figsize=(12, 8))
            for adder_type in self.adder_types:
                adder_df = operation_df[operation_df['adder_type'] == adder_type]
                if not adder_df.empty:
                    plt.plot(adder_df['rows'], adder_df['add_delay_ns'], marker='o', label=f"{adder_type}")
            
            plt.title(f"{operation} - Addition Delay vs Array Size")
            plt.xlabel("Array Size")
            plt.ylabel("Delay (ns)")
            plt.xscale('log', base=2)
            plt.grid(True)
            plt.legend()
            plt.savefig(os.path.join(self.results_csv_dir, f"{operation}_addition_delay.png"))
            plt.close()
            
            # Energy plot
            plt.figure(figsize=(12, 8))
            for adder_type in self.adder_types:
                adder_df = operation_df[operation_df['adder_type'] == adder_type]
                if not adder_df.empty:
                    plt.plot(adder_df['rows'], adder_df['add_energy_nJ'], marker='o', label=f"{adder_type}")
            
            plt.title(f"{operation} - Addition Energy vs Array Size")
            plt.xlabel("Array Size")
            plt.ylabel("Energy (nJ)")
            plt.xscale('log', base=2)
            plt.grid(True)
            plt.legend()
            plt.savefig(os.path.join(self.results_csv_dir, f"{operation}_addition_energy.png"))
            plt.close()
        
        # Compare bit-serial vs bit-parallel
        plt.figure(figsize=(12, 8))
        for operation in self.operations:
            operation_df = results_df[results_df['operation'] == operation]
            avg_delay = operation_df.groupby('rows')['add_delay_ns'].mean()
            plt.plot(avg_delay.index, avg_delay.values, marker='o', label=operation)
        
        plt.title("Average Addition Delay: Bit-Serial vs Bit-Parallel")
        plt.xlabel("Array Size")
        plt.ylabel("Delay (ns)")
        plt.xscale('log', base=2)
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(self.results_csv_dir, "bit_serial_vs_parallel_delay.png"))
        plt.close()
        
        # Energy comparison
        plt.figure(figsize=(12, 8))
        for operation in self.operations:
            operation_df = results_df[results_df['operation'] == operation]
            avg_energy = operation_df.groupby('rows')['add_energy_nJ'].mean()
            plt.plot(avg_energy.index, avg_energy.values, marker='o', label=operation)
        
        plt.title("Average Addition Energy: Bit-Serial vs Bit-Parallel")
        plt.xlabel("Array Size")
        plt.ylabel("Energy (nJ)")
        plt.xscale('log', base=2)
        plt.grid(True)
        plt.legend()
        plt.savefig(os.path.join(self.results_csv_dir, "bit_serial_vs_parallel_energy.png"))
        plt.close()

def main():
    parser = argparse.ArgumentParser(description='CACTI Neural Network Analysis Tool')
    parser.add_argument('--input_size', type=int, default=56, help='Input feature map size (default: 56)')
    parser.add_argument('--kernel_size', type=int, default=3, help='Kernel size (default: 3)')
    parser.add_argument('--input_channels', type=int, default=64, help='Number of input channels (default: 64)')
    parser.add_argument('--output_channels', type=int, default=64, help='Number of output channels (default: 64)')
    parser.add_argument('--output_dir', type=str, default='NN_Results', help='Output directory for results')
    
    args = parser.parse_args()
    
    wrapper = CACTIWrapper(output_dir=args.output_dir)
    results = wrapper.run_resnet_analysis(
        args.input_size, 
        args.kernel_size, 
        args.input_channels, 
        args.output_channels
    )
    
    print("Analysis complete. Results saved to:", args.output_dir)

if __name__ == "__main__":
    main()