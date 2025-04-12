# CACTI-6.5 for In-Memory Computing

This repository contains a modified version of CACTI 6.5, enhanced to model In-Memory Computing (IMC) capabilities with various sense amplifier designs and computational approaches for 28nm technology nodes.

## Overview

CACTI is an analytical tool that takes a set of cache/memory parameters as input and calculates its access time, power, cycle time, and area. This modified version extends CACTI to model in-memory computation using different sense amplifier designs and computational approaches, enabling design space exploration for IMC architectures.

## Features

### Original CACTI Features
- Power, delay, area, and cycle time model for:
  - Direct mapped caches
  - Set-associative caches
  - Fully associative caches
  - Embedded DRAM memories
  - Commodity DRAM memories
- Support for multi-ported uniform cache access (UCA) and non-uniform cache access (NUCA)
- Leakage power calculation considering operating temperature
- Router power model
- Interconnect model with various delay, power, and area properties
- Interface for trade-off analysis
- Support for multiple technology nodes (90nm, 65nm, 45nm, 32nm)

### IMC Extensions
- Bit-serial and bit-parallel computation modes
- Sense amplifier designs:
  - Conventional (CONV)
  - Memory Read Sense Amplifier (MRSA)
  - Computing-Enabled Sense Amplifier (CESA)
- Adder implementations:
  - BLADE (Bitline Latch-based ADdEr)
  - ISCAS-style
  - NEW design
  - DAC (Dynamic Adaptive Computing)
  - CRAM (Computational RAM)
- Neural network computation modeling with various memory mapping strategies

## Setup

### Prerequisites
- C++ compiler (GCC recommended)
- Python 3.6+ with numpy, pandas, matplotlib, and json
- Make

### Installation

1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd CACTI-6.5-master_28nm_IMC_SA
   ```

2. Compile the code:
   ```bash
   make clean
   make
   ```

3. Verify the installation:
   ```bash
   ./cacti -infile cache.cfg
   ```

## Basic Usage

### Running a Basic Simulation

1. Define your cache configuration in `cache.cfg`
2. Run CACTI:
   ```bash
   ./cacti -infile cache.cfg
   ```
3. Review the results in the output

### Configuration Options

The configuration file (`cache.cfg`) allows you to specify various parameters:

- Cache size (bytes)
- Block/line size (bytes)
- Associativity
- Technology node
- Design objectives (delay, power, area)
- For IMC: operation type, sense amplifier, and adder type

### IMC-Specific Parameters

For in-memory computing, additional parameters in `cache_bs_bp.cfg` include:

- `-Operation type-`: Set to either "bit_serial" or "bit_parallel"
- `-Sense AMP-`: Set to "CONV", "MRSA", or "CESA"
- `-Adder type -`: Set to "blade", "iscas", "new", "dac", or "cram"
- `-Nbits`: Number of bits for computation (typically 8)

Example configuration with IMC parameters:
```
-Operation type- "bit_parallel"
-Sense AMP- "CESA"
-Adder type - "blade"
-Nbits 8
```

## Running Batch Simulations

### Using Python Scripts

The repository includes Python scripts to automate running multiple simulations:

1. `Python_File_Himanshu.py`: Runs simulations for different adder types and array configurations

```bash
python Python_File_Himanshu.py
```

2. Jupyter notebooks (`bit_parallel.ipynb`, `bit_serial.ipynb`): Analyze and visualize results

## Neural Network Model Wrapper

The enhanced neural wrapper provides comprehensive analysis for different neural network architectures, including ResNet and Transformers, with advanced memory modeling capabilities to provide more realistic design space exploration.

### Using the Neural Wrapper

```bash
python neural_wrapper.py --model resnet --input_size 56 --kernel_size 3 --input_channels 64 --output_channels 64 --mapping weight_stationary
```

```bash
python neural_wrapper.py --model transformer --seq_len 512 --hidden_size 768 --num_heads 12
```

### Neural Wrapper Parameters:
- `--model`: Neural network model to analyze (resnet, transformer)
- `--input_size`: Input feature map size for ResNet (default: 56)
- `--kernel_size`: Kernel size for ResNet (default: 3)
- `--input_channels`: Number of input channels for ResNet (default: 64)
- `--output_channels`: Number of output channels for ResNet (default: 64)
- `--seq_len`: Sequence length for transformer models (default: 512)
- `--hidden_size`: Hidden dimension for transformer models (default: 768)
- `--num_heads`: Number of attention heads for transformer models (default: 12)
- `--mapping`: Memory mapping strategy (weight_stationary, output_stationary, input_stationary)
- `--output_dir`: Output directory for results (default: NN_Results)
- `--bit_precision`: Bit precision for calculations (default: 8)
- `--fixed_cache_size`: Fixed cache size in bytes (e.g., 65536 for 64KB) instead of scaling with array dimensions
- `--no_force_config`: Allow CACTI to determine optimal cache organization instead of forcing specific parameters. The selected configuration can be viewed in the output files under the respective operation type, adder type, and sense amplifier directories (e.g., `NN_Results_*/bit_parallel/new/CESA/array_256x256.txt`), which show values like Best Ndwl, Ndbl, Nspd, Ndcm, etc.

### Neural Wrapper Features:
The neural wrapper now includes:

1. **Workload-specific analysis**
   - Support for both ResNet and Transformer models
   - Detailed performance metrics calculation
   - Layer-by-layer analysis

2. **Automatic recommendation system**
   - Finds optimal configurations for throughput, energy, and latency
   - Generates human-readable recommendation files
   - Provides JSON output for programmatic use

3. **Memory mapping optimization**
   - Supports weight stationary, output stationary, and input stationary mappings
   - Calculates data reuse factors for each strategy
   - Analyzes impact of different mapping strategies on performance

4. **Comprehensive metrics**
   - Throughput (GOPS)
   - Energy efficiency (GOPS/W)
   - Memory access patterns
   - Total execution time
   - Area efficiency

5. **Enhanced memory modeling**
   - Option to use fixed cache size across different array organizations
   - Support for CACTI-optimized memory organization (automatically determines optimal Ndwl, Ndbl, Nspd, Ndcm values)
   - Improved error handling for incompatible configurations
   - Memory organization details are visible in output files showing parameters like "Best Ndwl", "Best Ndbl", etc.

### Output Files:
The neural wrapper creates:
- A directory structure organized by operation type, adder type, and sense amplifier
- CSV files with detailed results
- JSON files with optimization recommendations
- Human-readable recommendation files (.txt)
- Plots comparing performance metrics across configurations
- Memory mapping strategy comparisons

## Understanding Results

CACTI outputs include:
- Access time (ns)
- Cycle time (ns)
- Dynamic energy per access (nJ)
- Leakage power (mW)
- Area (mm²)

For IMC operations, additional metrics include:
- Compute adder delay (ns)
- Bit-serial delay for N-bits addition/multiplication (ns)
- Energy per computation (nJ)
- Breakdown of energy consumption across components

For neural network analysis, additional metrics include:
- Throughput (GOPS)
- Energy efficiency (GOPS/W)
- Total MAC operations
- Memory access patterns and counts
- Total execution time (ns)
- Total energy consumption (nJ)

## Example Workflow

1. **Basic test**:
   ```bash
   ./cacti -infile cache.cfg
   ```

2. **IMC exploration**:
   ```bash
   # Modify cache_bs_bp.cfg for your parameters
   ./cacti -infile cache_bs_bp.cfg
   ```

3. **Large-scale exploration**:
   ```bash
   python Python_File_Himanshu.py
   ```

4. **Default ResNet analysis**:
   ```bash
   python neural_wrapper.py --model resnet --input_size 56 --kernel_size 3 --mapping input_stationary
   ```

5. **ResNet with fixed cache size**:
   ```bash
   python neural_wrapper.py --model resnet --input_size 56 --kernel_size 3 --mapping input_stationary --fixed_cache_size 65536
   ```

6. **ResNet with fixed cache size and auto-organization**:
   ```bash
   python neural_wrapper.py --model resnet --input_size 56 --kernel_size 3 --mapping input_stationary --fixed_cache_size 65536 --no_force_config
   ```

7. **Transformer analysis**:
   ```bash
   python neural_wrapper.py --model transformer --seq_len 512 --hidden_size 768 --num_heads 12
   ```

8. **Results analysis**: 
   - Review generated recommendation files in the `NN_Results/RESULTS_CSV/` directory
   - Examine throughput and energy efficiency plots
   - Compare memory mapping strategies using the generated comparison plots
   - For deeper insights, see the `neural_wrapper_improvements.md` file

## Directory Structure

- `*.cc`, `*.h`: Source code files
- `*.cfg`: Configuration files
- `Results/`: Directory containing simulation results
- `NN_Results/`: Directory containing neural network analysis results
- `*.ipynb`: Jupyter notebooks for analysis
- Executables:
  - `cacti`: Main CACTI binary
  - `neural_wrapper.py`: Neural network analysis script

## License

This software is based on CACTI 6.5, which was developed by HP and is available under its original license terms. The in-memory computing extensions are provided under the same terms.

## Contact

For questions or contributions, please contact:

[Your Contact Information]

## References

- Original CACTI paper: "Optimizing NUCA Organizations and Wiring Alternatives for Large Caches With CACTI 6.0" (MICRO 2007)
- [Additional IMC publications and references]