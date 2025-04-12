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
- Neural network computation modeling

## Setup

### Prerequisites
- C++ compiler (GCC recommended)
- Python 3.6+ with numpy, pandas, and matplotlib
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

We've added a neural wrapper that runs CACTI for neural network computations, particularly ResNet convolution layers.

### Using the Neural Wrapper

```bash
./neural_wrapper.py --input_size 56 --kernel_size 3 --input_channels 64 --output_channels 64
```

### Parameters:
- `--input_size`: Input feature map size (default: 56)
- `--kernel_size`: Kernel size (default: 3)
- `--input_channels`: Number of input channels (default: 64)
- `--output_channels`: Number of output channels (default: 64)
- `--output_dir`: Output directory for results (default: NN_Results)

### Output:
The neural wrapper creates:
- A directory structure organized by operation type, adder type, and sense amplifier
- CSV files with detailed results
- Plots comparing performance and energy efficiency across designs

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

4. **Neural network analysis**:
   ```bash
   ./neural_wrapper.py --input_size 56 --kernel_size 3
   ```

5. **Results analysis**: Open Jupyter notebooks like `BS_vs_BP_SAs.ipynb` to visualize and analyze results

## Directory Structure

- `*.cc`, `*.h`: Source code files
- `*.cfg`: Configuration files
- `Results/`: Directory containing simulation results
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