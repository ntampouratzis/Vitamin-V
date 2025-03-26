# RiVEC Bencmark Suite

## Overview

This version of the [RiVEC Benchmark Suite](https://github.com/RALC88/riscv-vectorized-benchmark-suite) includes optimizations for the High Performance Computing (Axpy, matmul, and spmv) kernels, now adapted to use m8_t instead of m1_t to better exploit wider vector configurations under RVV 1.0 (RISC-V Vector Extension 1.0). Additionally, the matmul kernel now uses a transposed B matrix layout to improve memory access patterns and computational efficiency. These enhancements are part of work supported by the Vitamin_V H2020 project. 

The updated kernels have been tested using GCC/G++ v13.1 within the gem5 v24.1.0.1 simulator environment and are also compatible with physical RISC-V hardware that supports RVV 1.0.



## Vectorized apps

| Application Name  | Application Domain            | Algorithmic Model     |
| ----------------- |------------------------------ | --------------------- |
| Axpy              | High Performance Computing    | BLAS                  |
| matmul            | High Performance Computing    | BLAS                  |
| spmv              | High Performance Computing    | BLAS                  |


## Axpy
### Compile using gcc/g++ with RISCV Vector Version

To compile axpy application run the command make followed by the application name
```
cd _axpy
make serial
make vector
make vector_m8
```
This will compile 3 versions of the application, namely serial, vector with m1_t, and vector with m8_t (our version).

It produces the ```axpy_serial.exe  axpy_vector.exe  axpy_vector_m8.exe``` inside bin directory.

### Running the axpy
```
./bin/axpy_serial.exe 4096
./bin/axpy_vector.exe 4096
./bin/axpy_vector_m8.exe 4096
```

## Matmul
### Compile using gcc/g++ with RISCV Vector Version

To compile matmul application run the command make followed by the application name
```
cd _matmul
make serial
make vector 
```
This will compile 3 versions of the application, namely serial, vector with m1_t, and vector with m8_t (our version).

It produces the ```matmul_serial.exe  matmul_vector.exe  matmul_vector_m8_T.exe``` inside bin directory.

### Running the matmul
```
./bin/matmul_serial.exe input/data_8192_Vitamin.in
./bin/matmul_vector.exe input/data_8192_Vitamin.in
./bin/matmul_vector_m8_T.exe input/data_8192_Vitamin.in
```

You can generate any matrix multiplication size using:
```
perl gendata.pl --dimM=128 --dimK=128 --dimN=128 --seed=42 > data_128.in
```

## Spmv
### Compile using gcc/g++ with RISCV Vector Version

To compile spmv application run the command make followed by the application name
```
cd _spmv
make serial
make vector
```
This will compile 3 versions of the application, namely serial, vector with m1_t, and vector with m8_t (our version).

It produces the ```spmv_serial.exe  spmv_vector.exe  spmv_vector_m8.exe``` inside bin directory.

### Running the spmv
```
./bin/spmv_serial.exe input/venkat25.mtx input/venkat25.verif
./bin/spmv_vector.exe input/venkat25.mtx input/venkat25.verif
./bin/spmv_vector_m8.exe input/venkat25.mtx input/venkat25.verif
```

## Contact
Nikolaos Tampouratzis
ntampouratzis@ihu.gr / tampouratzis@exapysys.eu
