# Neural Wrapper Guide

This comprehensive guide explains the neural wrapper tool for CACTI-6.5 with IMC extensions, covering what it is, why we made changes, how to use it, and detailed analysis of its outputs.

## 1. What is the Neural Wrapper?

The neural wrapper (`neural_wrapper.py`) is a specialized Python script that interfaces with the CACTI-6.5 IMC tool to systematically analyze in-memory computing architectures for different neural network workloads. It serves as a higher-level abstraction layer that:

- Translates neural network workload parameters into CACTI configuration parameters
- Automates running multiple CACTI simulations across architectural design spaces
- Calculates workload-specific performance metrics beyond basic CACTI outputs
- Analyzes and compares different IMC architectural approaches
- Recommends optimal configurations for specific optimization targets
- Generates visualizations and data files for further analysis

The wrapper allows researchers and designers to quickly explore how different IMC architectures perform for specific neural network operations without manually configuring and running hundreds of CACTI simulations.

## 2. Changes Made and Their Relevance

### 2.1 Original Limitations

The original neural wrapper had several limitations:

- Only supported basic ResNet convolutional layers
- Used a fixed memory mapping strategy without considering alternatives
- Lacked comprehensive performance metrics for neural network operations
- Did not provide automatic recommendations for optimal configurations
- Generated only basic plots without deeper architectural insights
- Did not account for memory access patterns and data reuse

### 2.2 Key Improvements

We implemented several major improvements to address these limitations:

#### 2.2.1 Workload-Specific Analysis
- **What**: Added support for multiple neural network architectures (ResNet, Transformers)
- **Why relevant**: Different neural networks have different computational patterns and memory requirements. Supporting multiple architectures allows for broader design space exploration relevant to modern AI workloads.
- **Impact**: Enables designers to optimize IMC architectures for specific neural network types rather than using a one-size-fits-all approach.

#### 2.2.2 Memory Mapping Strategies
- **What**: Implemented three different memory mapping strategies (weight stationary, output stationary, input stationary)
- **Why relevant**: Memory mapping significantly impacts data movement, which dominates energy consumption in neural network accelerators. Different mapping strategies prioritize different types of data reuse.
- **Impact**: Allows designers to explore memory access pattern optimizations and understand their effect on performance and energy efficiency.

#### 2.2.3 Automatic Recommendation System
- **What**: Created a system that automatically identifies optimal configurations for different optimization targets
- **Why relevant**: The design space is too large to manually analyze all configurations, and different applications prioritize different metrics (throughput, energy, latency).
- **Impact**: Provides immediate insights into which IMC configuration is best for a specific use case without requiring manual data analysis.

#### 2.2.4 Comprehensive Performance Metrics
- **What**: Added detailed performance metrics calculation based on workload characteristics
- **Why relevant**: Basic CACTI metrics (access time, energy per access) don't directly translate to neural network performance metrics (GOPS, energy efficiency).
- **Impact**: Provides application-relevant metrics that designers can use to make informed architectural decisions.

#### 2.2.5 Enhanced Visualization and Analysis
- **What**: Improved visualization capabilities with targeted, insightful plots
- **Why relevant**: Visual comparison helps identify trends and trade-offs that might be missed in raw data.
- **Impact**: Makes it easier to understand how different architectural choices affect performance and efficiency.

## 3. Updates to the Original Wrapper

### 3.1 Technical Changes

| Component | Original Implementation | Updated Implementation |
|-----------|-------------------------|------------------------|
| Supported Models | ResNet convolutional layers only | ResNet + Transformer architectures |
| Operation Types | Convolution only | Convolution, Matrix multiplication |
| Memory Mapping | Fixed (implicit) | Three explicit strategies with analysis |
| Performance Metrics | Basic (delay, energy) | Comprehensive (throughput, energy efficiency, etc.) |
| Recommendations | None | Automatic for multiple optimization targets |
| Precision | Fixed 8-bit | Configurable bit precision |
| Output Formats | CSV, PNG plots | CSV, PNG, JSON, TXT recommendations |

### 3.2 New Functions Added

| Function | Description | Relevance |
|----------|-------------|-----------|
| `calculate_memory_requirements()` | Calculates memory needs based on workload and mapping strategy | Enables explicit modeling of memory requirements and data reuse |
| `parse_network_layer()` | Translates neural network parameters to memory configurations | Supports different neural network architectures |
| `calculate_layer_performance()` | Computes comprehensive performance metrics | Provides application-relevant metrics beyond raw CACTI outputs |
| `find_optimal_configuration()` | Identifies best configurations for different goals | Enables automatic recommendations |
| `save_recommendations()` | Generates recommendation files | Makes results accessible in multiple formats |
| `compare_mapping_strategies()` | Analyzes impact of different mapping approaches | Helps understand the effect of memory mapping on performance |
| `run_transformer_analysis()` | Performs analysis for transformer architectures | Adds support for transformer models |

### 3.3 Code Structure Evolution

The code structure evolved from a simple script to a more modular, object-oriented design:

```
Original Structure:
- CACTIWrapper class with basic simulation functionality
- run_resnet_analysis() method
- extract_results() and generate_summary_plots() methods
- main() function with basic argument parsing

Enhanced Structure:
- Expanded CACTIWrapper class with comprehensive methods
- Memory mapping strategy implementation and analysis
- Modular workload-specific analysis functions
- Recommendation engine components
- Enhanced visualization capabilities
- Advanced CLI with model-specific parameters
```

## 4. How to Use the NN_Results

The neural wrapper generates a rich set of output files in the `NN_Results` directory, organized as follows:

```
NN_Results/
├── bit_parallel/               # Results for bit-parallel configurations
│   ├── [adder_type]/           # Organized by adder implementation
│   │   └── [sense_amp]/        # Organized by sense amplifier design
│   │       └── array_*x*.txt   # Raw CACTI output files for each array size
├── bit_serial/                 # Results for bit-serial configurations
│   └── [similar structure]
└── RESULTS_CSV/                # Processed results and analysis
    ├── [model]_results.csv     # Complete results in CSV format
    ├── [model]_recommendations.json  # Machine-readable recommendations
    ├── [model]_recommendations.txt   # Human-readable recommendations
    ├── [model]_strategy_comparison.json  # Mapping strategy comparison
    ├── [model]_throughput.png         # Throughput vs Array Size plot
    ├── [model]_energy_efficiency.png  # Energy Efficiency vs Array Size plot
    └── [model]_mapping_impact.png     # Impact of memory mapping strategies
```

### 4.1 Key Output Files

#### 4.1.1 CSV Results File

The comprehensive CSV file (`[model]_results.csv`) contains all simulation results with columns including:

- Basic parameters: array size, operation type, adder type, sense amp, etc.
- Memory requirements: weights, inputs, outputs in bytes
- Data reuse factors for each memory mapping strategy
- Performance metrics: throughput, energy efficiency, execution time
- Detailed timing breakdown: compute time, memory access time
- Detailed energy breakdown: compute energy, memory access energy

This file can be imported into data analysis tools for further exploration.

#### 4.1.2 Recommendation Files

Two recommendation files are generated:

1. **[model]_recommendations.txt**: Human-readable file with clear sections for:
   - Overall best configuration (throughput-optimized)
   - Energy-efficient configuration
   - Latency-optimized configuration
   - Each section includes specific parameters and performance metrics

2. **[model]_recommendations.json**: Machine-readable JSON file with the same information, useful for automated tools or scripts.

#### 4.1.3 Visualization Files

The wrapper generates several PNG files:

- **[model]_throughput.png**: Shows how throughput varies with array size for different operation types.
- **[model]_energy_efficiency.png**: Shows how energy efficiency varies with array size.
- **[model]_mapping_impact.png**: Compares the impact of different memory mapping strategies.
- **[model]_strategy_comparison.png**: Bar chart comparing average performance across mapping strategies.

#### 4.1.4 Raw CACTI Output

The individual `.txt` files in the `bit_parallel/` and `bit_serial/` directories contain the raw CACTI output for each specific configuration. These are useful for debugging or extracting additional metrics not processed by the wrapper.

### 4.2 Interpreting the Results

#### 4.2.1 Recommendations

The recommendation files provide a straightforward way to identify the optimal configuration:

```
BEST OVERALL CONFIGURATION (THROUGHPUT-OPTIMIZED)
--------------------------------------------------
Array Size: 64x64
Operation: bit_parallel
Adder Type: new
Sense Amplifier: CESA
Mapping Strategy: input_stationary
Throughput: 3.46 GOPS
Energy Efficiency: 348.29 GOPS/W
```

This tells you that for the specific workload analyzed, a 64x64 array using bit-parallel operation with the "new" adder type, CESA sense amplifier, and input-stationary mapping provides the highest throughput.

#### 4.2.2 Performance Trends

The visualization files help understand trends and trade-offs:

- If throughput increases with array size, it suggests computation is the bottleneck.
- If throughput plateaus or decreases with larger arrays, it suggests memory access or other factors are limiting performance.
- Differences between bit-serial and bit-parallel lines show the trade-off between these approaches.
- Comparing different mapping strategies shows which one is best for a specific workload.

## 5. Generated Figures Analysis

### 5.1 Figure Correctness

The figures generated by the neural wrapper are generally correct, but with some important considerations:

1. **Model-specific figures**: The tool generates figures specific to the last model run. If you ran the transformer model last, you'll see `matmul_*.png` files; if you ran ResNet last, you'll see `conv_*.png` files.

2. **Matching raw data**: The figures should match the trends in the CSV files. If there's a discrepancy, it could indicate a bug in the plotting code or data processing.

3. **Expected trends**: For most architectures, we expect to see:
   - Throughput initially increasing with array size, then potentially plateauing or decreasing for very large arrays
   - Energy efficiency potentially peaking at a moderate array size
   - Bit-parallel generally showing higher throughput but potentially lower energy efficiency than bit-serial

4. **Mapping strategies impact**: Different mapping strategies should show different performance characteristics depending on the workload.

### 5.2 Why Only Figures for MatMul?

If you're only seeing figures for matrix multiplication operations, it's because the last neural network model you analyzed was a transformer, which primarily uses matrix multiplications. The neural wrapper overwrites the previous results directory by default, so only the most recent run's results are preserved.

To generate figures for convolutional operations:

```bash
python neural_wrapper.py --model resnet --input_size 56 --kernel_size 3 --input_channels 64 --output_channels 64
```

To preserve previous results, use a different output directory:

```bash
python neural_wrapper.py --model resnet --output_dir NN_Results_ResNet
python neural_wrapper.py --model transformer --output_dir NN_Results_Transformer
```

### 5.3 Throughput and Energy Not Changing with Array Size

If the throughput and energy efficiency don't change significantly with array size for bit-serial operations, several factors could explain this:

1. **Memory access domination**: If memory access time dominates computation time, changing the array size might not significantly affect overall performance.

2. **Implementation issues**: There might be bugs in how bit-serial performance is calculated or how array size affects the calculations.

3. **Scaling limits**: There might be fundamental limits to how bit-serial operations scale with array size in the current implementation.

4. **Data normalization**: The y-axis scale might be making small changes appear flat if there are large differences between bit-serial and bit-parallel values.

To investigate this issue:

1. Examine the CSV data directly to confirm if the values are truly constant
2. Check the `calculate_layer_performance()` function for how bit-serial performance is calculated
3. Modify the `generate_summary_plots()` function to use separate plots or logarithmic scales for bit-serial and bit-parallel
4. Try running with different workload parameters to see if the issue persists

## 6. Using the Neural Wrapper

### 6.1 Basic Usage

#### 6.1.1 For ResNet Analysis

```bash
python neural_wrapper.py --model resnet --input_size 56 --kernel_size 3 --input_channels 64 --output_channels 64 --mapping weight_stationary
```

Parameters:
- `--input_size`: Size of the input feature map (default: 56)
- `--kernel_size`: Size of the convolutional kernel (default: 3)
- `--input_channels`: Number of input channels (default: 64)
- `--output_channels`: Number of output channels (default: 64)

#### 6.1.2 For Transformer Analysis

```bash
python neural_wrapper.py --model transformer --seq_len 512 --hidden_size 768 --num_heads 12
```

Parameters:
- `--seq_len`: Sequence length for transformer models (default: 512)
- `--hidden_size`: Hidden dimension size (default: 768)
- `--num_heads`: Number of attention heads (default: 12)

#### 6.1.3 Common Parameters

- `--mapping`: Memory mapping strategy (weight_stationary, output_stationary, input_stationary)
- `--output_dir`: Directory to store results (default: NN_Results)
- `--bit_precision`: Bit precision for calculations (default: 8)

### 6.2 Advanced Usage

#### 6.2.1 Running Multiple Mapping Strategies

The wrapper automatically runs all mapping strategies for ResNet analysis, but you can specify a particular one:

```bash
python neural_wrapper.py --model resnet --mapping weight_stationary
```

#### 6.2.2 Customizing Bit Precision

Adjust the bit precision for calculations:

```bash
python neural_wrapper.py --model resnet --bit_precision 16
```

#### 6.2.3 Comparing Specific Architectures

For detailed comparison of specific architectures, extract and analyze the CSV results:

```python
import pandas as pd
results = pd.read_csv('NN_Results/RESULTS_CSV/conv_results.csv')

# Filter for specific configurations
bit_parallel = results[results['operation'] == 'bit_parallel']
bit_serial = results[results['operation'] == 'bit_serial']

# Compare specific adder types
blade_results = results[results['adder_type'] == 'blade']
new_results = results[results['adder_type'] == 'new']

# Find best configuration for specific metric
best_throughput = results.iloc[results['throughput_gops'].idxmax()]
best_energy = results.iloc[results['energy_efficiency_gops_per_w'].idxmax()]
```

## 7. Extending the Neural Wrapper

### 7.1 Adding New Neural Network Models

To add support for a new neural network model:

1. Add a new function similar to `run_resnet_analysis()` or `run_transformer_analysis()`
2. Implement the appropriate parameter parsing and layer representation
3. Add the model to the CLI options in the `main()` function
4. Update the `calculate_layer_performance()` function if new operations are needed

### 7.2 Adding New Memory Mapping Strategies

To add a new memory mapping strategy:

1. Extend the `mapping_strategies` list in the `__init__` method
2. Add the strategy to the `calculate_memory_requirements()` function
3. Add data reuse factor calculations for the new strategy
4. Update the `calculate_layer_performance()` function to handle the new strategy

### 7.3 Adding New Performance Metrics

To add new performance metrics:

1. Calculate the metric in the `calculate_layer_performance()` function
2. Add the metric to the result dictionary
3. Update the `find_optimal_configuration()` function to consider the new metric
4. Add visualization support in `generate_summary_plots()` if needed

## 8. Common Issues and Troubleshooting

### 8.1 CACTI Configuration Issues

If the wrapper fails to run CACTI simulations:

1. Ensure CACTI is properly compiled and executable
2. Check that the `cache_bs_bp.cfg` template exists and is readable
3. Verify that the parameters being set are valid for your CACTI version
4. Check the CACTI output files for specific error messages

### 8.2 Performance Calculation Issues

If performance metrics seem incorrect:

1. Review the `calculate_layer_performance()` function for any calculation errors
2. Check that data reuse factors are calculated correctly for your mapping strategy
3. Verify that memory access patterns are being modeled appropriately
4. Compare with manual calculations for a simple test case

### 8.3 Visualization Issues

If plots don't display or have incorrect information:

1. Ensure matplotlib is properly installed
2. Check that the data being plotted exists in the results DataFrame
3. Verify the data ranges to ensure small differences aren't being obscured by the scale
4. Try generating separate plots for different operation types or metrics

## 9. Future Improvements

Several future improvements could enhance the neural wrapper:

1. **Multi-layer analysis**: Extend to analyze complete networks with multiple layers
2. **Dataflow optimizations**: Add more sophisticated dataflow and scheduling optimizations
3. **Quantization support**: Add analysis of different precision configurations
4. **Hardware utilization**: Model hardware utilization and efficiency metrics
5. **Runtime memory analysis**: Add dynamic memory usage analysis during network execution
6. **Power delivery analysis**: Add modeling of power delivery constraints
7. **Integration with ML frameworks**: Direct import of models from PyTorch or TensorFlow
8. **Reliability analysis**: Add analysis of reliability and fault tolerance

## 10. Conclusion

The neural wrapper provides a powerful tool for exploring the design space of in-memory computing architectures for neural network workloads. By automating the configuration, execution, and analysis of CACTI simulations, it enables researchers and designers to quickly identify optimal architectures for specific applications and optimization targets.

The enhanced version adds support for different neural network models, memory mapping strategies, and comprehensive performance metrics, making it a valuable tool for IMC architecture design and optimization. By understanding how to use and interpret its outputs, designers can make informed decisions about architectural trade-offs and optimizations.