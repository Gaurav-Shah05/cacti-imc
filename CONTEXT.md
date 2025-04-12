# CACTI-6.5 for In-Memory Computing (Context for LLMs)

This document provides technical context about the repository for large language models to better understand the codebase.

## Project Overview

This repository contains a modified version of CACTI 6.5, a well-established memory modeling tool developed by HP, extended to model In-Memory Computing (IMC) capabilities. The original CACTI tool allows designers to estimate the access time, power consumption, area, and cycle time of various cache/memory organizations. 

This extension adds the capability to model in-memory computing operations using different sense amplifier designs and computational approaches specifically for 28nm technology node. It supports both bit-serial and bit-parallel computation modes, different sense amplifier architectures, and various adder implementations to enable comprehensive design space exploration for IMC systems.

## Technical Architecture

### Core Components

1. **CACTI Core (Original) Components**:
   - `cacti_interface.{cc,h}`: Main interface for the tool
   - `io.{cc,h}`: Handles I/O operations
   - `parameter.{cc,h}`: Manages configuration parameters
   - `technology.cc`: Contains technology node specific parameters
   - `basic_circuit.{cc,h}`: Models basic circuit components like decoders, drivers
   - `component.{cc,h}`: Higher-level building blocks
   - `subarray.{cc,h}`, `mat.{cc,h}`, `bank.{cc,h}`: Memory organization levels
   - `area.{cc,h}`, `wire.{cc,h}`: Physical modeling of area and interconnects
   - `nuca.{cc,h}`: Models non-uniform cache access architectures

2. **IMC Extensions**:
   - Sense amplifier implementations:
     - CONV: Conventional sense amplifier
     - MRSA: Memory Read Sense Amplifier (optimized for read operations)
     - CESA: Computing-Enabled Sense Amplifier (optimized for computing)
   
   - Adder implementations:
     - `adderBLADE.{cc,h}`: Bitline Latch-based ADdEr
     - `adderCRAM.{cc,h}`: Computational RAM approach
     - `adderDAC.{cc,h}`: Dynamic Adaptive Computing approach
     - `adderISCAS.{cc,h}`: ISCAS-style adder
     - `addernew.{cc,h}`: A new adder implementation
     
   - Multiplier implementations:
     - `multiplier_parallel.{cc,h}`: Bit-parallel multiplier
     - `multiplier_serial_*.{cc,h}`: Various bit-serial multiplier implementations

3. **Data Extraction and Analysis**:
   - `extractData.{cc,h}`: Extracts and processes results
   - Python scripts and Jupyter notebooks for batch processing and visualization

### Runtime Flow

1. **Initialization and Configuration**:
   - Parse configuration file with memory parameters and IMC-specific settings
   - Initialize technology parameters based on selected node
   
2. **Memory Organization Calculation**:
   - Determine optimal memory organization (Ndwl, Ndbl, Nspd, etc.)
   - Model subarray, mat, and bank structures
   
3. **Circuit Simulation**:
   - Model circuit-level behavior for memory access and IMC operations
   - Calculate timing and energy values for different components
   
4. **IMC Operation Modeling**:
   - Model in-memory operations using selected sense amplifier and adder designs
   - Calculate latency and energy for bit-serial or bit-parallel operations
   
5. **Results Collection and Analysis**:
   - Extract and process simulation results
   - Generate comprehensive output with timing, energy, and area metrics

## IMC Implementation Details

### Bit-Serial vs Bit-Parallel Computation

- **Bit-Serial**: Processes computations bit by bit, requiring multiple cycles but using simpler hardware
  - Implemented in `multiplier_serial_*.{cc,h}` files
  - Lower peak power but higher total energy and latency
  
- **Bit-Parallel**: Processes all bits simultaneously
  - Implemented in `multiplier_parallel.{cc,h}`
  - Higher throughput but more complex hardware

### Sense Amplifier Architectures

Each sense amplifier design has different trade-offs in terms of speed, energy efficiency, and area:

- **CONV**: Standard differential sense amplifier
- **MRSA**: Optimized for fast reading with lower energy consumption
- **CESA**: Specialized for computation with additional logic for in-memory operations

### Adder Implementations

The codebase supports multiple adder implementations with varying architectural approaches:

- **BLADE**: Uses latch-based design with bitline computing
- **ISCAS**: Based on standard ISCAS benchmark designs
- **NEW**: A novel implementation with optimizations for IMC
- **DAC**: Dynamic Adaptive Computing approach with reconfigurability
- **CRAM**: Computational RAM approach integrating logic with memory cells

## Neural Network Wrapper

The `neural_wrapper.py` script provides a high-level interface for exploring IMC architectures in the context of neural network computations. It specifically focuses on convolutional layers commonly found in ResNet architectures.

The wrapper:
1. Converts neural network layer parameters into memory configuration parameters
2. Runs CACTI simulations for various IMC architectures
3. Extracts relevant metrics (latency, energy, etc.)
4. Generates comparison plots and detailed CSV results

## Repository Structure Analysis

- `*.cc`, `*.h`: C++ source and header files
- `*.cfg`: Configuration files with different parameter sets
- Results directories:
  - `Results/`: Main results directory
  - `Results_NS/`, `Results_NS_*/`: Results for non-square subarray configurations
- Jupyter notebooks (`*.ipynb`): Analysis scripts for processing results
- Python scripts:
  - `Python_File_Himanshu.py`: Automation script for batch simulations
  - `neural_wrapper.py`: Neural network model wrapper
- Binary:
  - `cacti`: Main executable
- Output files:
  - `*.txt`: Raw CACTI output files
  - `*.csv`: Processed results in tabular format

## Implementation Quirks and Technical Notes

- The original CACTI code has been significantly modified to support IMC operations
- The IMC operations are modeled at the subarray level
- Timing and energy values are calculated at a fine-grained level
- Both computation and memory access are modeled in an integrated fashion
- Technology parameters are specific to 28nm
- The tool assumes a fixed 8-bit precision for most computations

## Relevant Technical Papers

1. Original CACTI: "Optimizing NUCA Organizations and Wiring Alternatives for Large Caches With CACTI 6.0" (MICRO 2007)
2. PIM computing: Various papers on Processing-In-Memory architectures
3. IMC design: Papers describing the specific IMC architectures implemented (BLADE, CRAM, etc.)