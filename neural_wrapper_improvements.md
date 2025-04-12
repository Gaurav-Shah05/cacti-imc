# Neural Wrapper Enhancements for CACTI-6.5 IMC

## Summary of Enhancements

We've made several key enhancements to the neural_wrapper.py script to provide more realistic memory modeling and configuration options:

### 1. Fixed Cache Size Support

- **Problem**: Originally, the cache size was directly tied to array dimensions (rows×cols), leading to artificial comparisons between very different memory capacities
- **Enhancement**: Added `--fixed_cache_size` parameter to specify a consistent memory capacity across different array organizations
- **Benefit**: Allows fair comparison between different memory organizations with the same total memory budget

### 2. Configurable Cache Organization

- **Problem**: The wrapper was forcing a specific cache organization (single bank, single array) by setting all Ndwl, Ndbl, etc. parameters to 1
- **Enhancement**: Added `--no_force_config` flag to let CACTI automatically determine the optimal organization for a given memory capacity
- **Benefit**: Leverages CACTI's optimization to find the best memory organization for different array sizes
- **Visibility**: The selected configuration parameters (Best Ndwl, Ndbl, Nspd, Ndcm, etc.) can be seen in the output files found in the respective array directories

### 3. Improved Error Handling

- **Problem**: The script would fail when configurations led to invalid results or empty dataframes
- **Enhancement**: Added comprehensive error handling throughout the workflow
- **Benefit**: More robust execution even with experimental or edge-case configurations

## Findings from Comparative Analysis

We ran tests across three configurations:

### Configuration 1: Default (Cache Size Scales with Array Size)
- Cache size depends on array dimensions (rows×cols÷8 bytes)
- Forces specific organization with single bank and array
- **Findings**:
  - Smaller arrays (64×64) provided better throughput (3.11 GOPS) and energy efficiency (331.37 GOPS/W)
  - Performance decreased monotonically with increasing array size
  - Optimal: Bit-parallel, NEW adder, CESA sense amp, input-stationary mapping, 64×64 array

### Configuration 2: Fixed Size, Forced Organization
- Fixed 64KB cache size regardless of array dimensions
- Forces specific organization with single bank and array
- **Findings**:
  - Not all array configurations were compatible with the fixed size
  - Similar general trends, but with different absolute performance numbers
  - Many configurations showed incompatibilities or suboptimal results

### Configuration 3: Fixed Size, Auto-Organization
- Fixed 64KB cache size regardless of array dimensions
- Allows CACTI to optimize the memory organization
- **Findings**:
  - Performance characteristics changed dramatically
  - Larger arrays (1024×1024) achieved best throughput (2.76 GOPS)
  - Energy efficiency peaked at mid-sized arrays (256×256, 61.04 GOPS/W)
  - Non-monotonic relationship between array size and performance
  - Same optimal components: Bit-parallel, NEW adder, CESA sense amp, input-stationary mapping
  - CACTI selected different memory organizations for each array size:
    - 256×256 array: Ndwl=2, Ndbl=1, Nspd=4, Ndcm=4
    - 1024×1024 array: Different organization optimized for larger arrays

## Technical Limitations

The current implementation of the neural wrapper has several technical limitations that should be addressed in future work:

1. **Tiling and Array Size Limitations**:
   - The wrapper doesn't implement tiling strategies when operations exceed array dimensions
   - Example: A 64×64 array can't directly compute a 128×128 matrix multiplication
   - The model currently assumes all computation fits within the specified array size
   - Impact: Performance metrics may be unrealistic for larger workloads

2. **Memory Access Modeling Limitations**:
   - Memory access patterns don't account for distributed arrays with data dependencies
   - No modeling of inter-array communication overhead for tiled operations
   - Impact: Underestimates memory access time and energy for large workloads

3. **Computation Model Simplifications**:
   - Uses simplified computation models that don't fully account for hardware constraints
   - Bit-parallel multiplier characteristics are approximated based on adder characteristics
   - Impact: Doesn't accurately model real hardware limitations like broadcast constraints

4. **Mapping Strategy Implementation Issues**:
   - Mapping strategies (weight/input/output-stationary) are implemented at a high level
   - The hardware implications of these strategies aren't fully modeled
   - Impact: May underestimate performance differences between mapping strategies

5. **Performance Metric Calculation Limitations**:
   - Assumes ideal execution without accounting for array utilization
   - Doesn't incorporate tiling overhead in calculations
   - Impact: Reported metrics may be overly optimistic, especially for larger workloads

## Recommendations for Future Enhancements

1. **Implement Tiling Strategies**:
   - Add methods to decompose large operations into tiles that fit array dimensions
   - Calculate additional overhead for inter-tile communication
   - Model utilization factors when operations don't perfectly fit arrays

2. **Enhance Memory Access Modeling**:
   - Model hierarchical memory access patterns for tiled operations
   - Account for data movement between arrays
   - Implement more realistic data reuse models based on hardware constraints

3. **Improve Computation Modeling**:
   - Implement cycle-accurate simulation for bit-serial operations
   - Better model multiplier operations instead of approximating from adder characteristics
   - Account for array utilization factors in performance calculations

4. **Refine Mapping Strategy Implementation**:
   - Implement detailed dataflow models for each mapping strategy
   - Account for practical constraints in dataflow implementation
   - Model impact of mapping strategies on tiled operations

5. **Add Configuration Validation**:
   - Implement checks to validate whether workloads can execute on given array configurations
   - Warn users when configurations are unrealistic
   - Provide guidance on appropriate tiling strategies

## Design Recommendations

1. **For Research Comparisons**:
   - Use fixed cache size with automatic organization for most realistic modeling
   - Compare against scaled cache size for understanding raw array performance
   - Be aware of the tiling limitations when interpreting results for large workloads

2. **For Memory Architecture Design**:
   - Bit-parallel operations consistently outperform bit-serial (3-4 GOPS vs 0.01-0.1 GOPS)
   - CESA sense amplifiers provide the best balance of performance and energy efficiency
   - NEW adder implementation is consistently optimal across test configurations
   - Input-stationary mapping strategy provides the best performance for convolutional workloads

3. **For Optimal Array Sizing**:
   - For maximum throughput: Use larger arrays (1024×1024) with optimized organization
   - For best energy efficiency: Use moderate-sized arrays (256×256) with optimized organization
   - For latency-sensitive applications: Similar recommendations as throughput

## Usage Examples

```bash
# Default configuration (cache size scales with array dimensions)
python neural_wrapper.py --model resnet --input_size 8 --kernel_size 3 --input_channels 8 --output_channels 8 --output_dir NN_Results_Default

# Fixed cache size with forced organization
python neural_wrapper.py --model resnet --input_size 8 --kernel_size 3 --input_channels 8 --output_channels 8 --fixed_cache_size 65536 --output_dir NN_Results_Fixed_Size

# Fixed cache size with automatic organization (most realistic)
python neural_wrapper.py --model resnet --input_size 8 --kernel_size 3 --input_channels 8 --output_channels 8 --fixed_cache_size 65536 --no_force_config --output_dir NN_Results_Fixed_Size_Auto_Org
```
