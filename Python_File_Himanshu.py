##SCRIPT FOR SENSE AMPS

# import os

# def modify_config(file_path, size, block_size, bus_width, operation, sense_amp):
#     with open(file_path, 'r') as file:
#         lines = file.readlines()
    
#     with open(file_path, 'w') as file:
#         for line in lines:
#             if line.startswith("-size (bytes)"):
#                 file.write(f"-size (bytes) {size}\n")
#             elif line.startswith("-block size (bytes)"):
#                 file.write(f"-block size (bytes) {block_size}\n")
#             elif line.startswith("-output/input bus width"):
#                 file.write(f"-output/input bus width {bus_width}\n")
#             elif line.startswith("-Operation type") or line.startswith("# -Operation type"):
#                 file.write(f"-Operation type- \"{operation}\"\n")
#             elif "-Sense AMP-" in line:
#                 if f'"{sense_amp}"' in line:
#                     file.write(f"-Sense AMP- \"{sense_amp}\"\n")
#                 else:
#                     file.write(f"# {line}")
#             else:
#                 file.write(line)

# def run_simulation():
#     file_path = "cache_bs_bp.cfg"
#     square_sizes = [64, 128, 256, 512, 1024]
#     non_square_sizes = [(32, 256), (32, 512), (32, 1024),
#                          (64, 256), (64, 512), (64, 1024),
#                          (128, 256), (128, 512), (128, 1024)]
#     operations = ["bit_serial", "bit_parallel"]
#     sense_amps = ["CONV", "MRSA", "CESA"]
    
#     for size in square_sizes:
#         row, col = size, size
#         for operation in operations:
#             for sense_amp in sense_amps:
#                 cache_size = (row * col) // 8
#                 block_size = col // 8
#                 bus_width = col
#                 modify_config(file_path, cache_size, block_size, bus_width, operation, sense_amp)
#                 os.system(f"./cacti -infile {file_path}")
    
#     for row, col in non_square_sizes:
#         for operation in operations:
#             for sense_amp in sense_amps:
#                 cache_size = (row * col) // 8
#                 block_size = col // 8
#                 bus_width = col
#                 modify_config(file_path, cache_size, block_size, bus_width, operation, sense_amp)
#                 os.system(f"./cacti -infile {file_path}")
                
# if __name__ == "__main__":
#     run_simulation()


##SCRIPT FOR ADDERS

import os

def modify_config(file_path, size, block_size, bus_width, operation, adder_type):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    
    with open(file_path, 'w') as file:
        for line in lines:
            if line.startswith("-size (bytes)"):
                file.write(f"-size (bytes) {size}\n")
            elif line.startswith("-block size (bytes)"):
                file.write(f"-block size (bytes) {block_size}\n")
            elif line.startswith("-output/input bus width"):
                file.write(f"-output/input bus width {bus_width}\n")
            elif line.startswith("-Operation type") or line.startswith("# -Operation type"):
                file.write(f"-Operation type- \"{operation}\"\n")
            elif line.startswith("-Adder type") or line.startswith("# -Adder type"):
                file.write(f"-Adder type - \"{adder_type}\"\n")
            else:
                file.write(line)

def run_simulation():
    file_path = "cache_bs_bp.cfg"
    square_sizes = [64, 128, 256, 512, 1024]
    non_square_sizes = [(32, 256), (32, 512), (32, 1024),
                         (64, 256), (64, 512), (64, 1024),
                         (128, 256), (128, 512), (128, 1024)]
    operations = ["bit_serial", "bit_parallel"]
    adder_types = ["blade", "iscas", "new", "dac", "cram"]
    
    for size in square_sizes:
        row, col = size, size
        for operation in operations:
            for adder_type in adder_types:
                cache_size = (row * col) // 8
                block_size = col // 8
                bus_width = col
                modify_config(file_path, cache_size, block_size, bus_width, operation, adder_type)
                os.system(f"./cacti -infile {file_path}")
    
    for row, col in non_square_sizes:
        for operation in operations:
            for adder_type in adder_types:
                cache_size = (row * col) // 8
                block_size = col // 8
                bus_width = col
                modify_config(file_path, cache_size, block_size, bus_width, operation, adder_type)
                os.system(f"./cacti -infile {file_path}")
                
if __name__ == "__main__":
    run_simulation()
