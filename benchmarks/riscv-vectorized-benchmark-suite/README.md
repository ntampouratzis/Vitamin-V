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



## Matmul
### Compile using gcc/g++ with RISCV Vector Version

To compile matmul application run the command make followed by the application name
```
cd _matmul
make serial
make vector 
```
This will compile two versions of the application, namely serial, vector with m1_t, and vector with m8_t (our version).

It produces the ```matmul_serial.exe  matmul_vector.exe  matmul_vector_m8_T.exe``` inside bin directory.

### Running the Vectorized apps
```
./bin/matmul_serial.exe input/data_8192_Vitamin.in
./bin/matmul_vector.exe input/data_8192_Vitamin.in
./bin/matmul_vector_m8_T.exe input/data_8192_Vitamin.in
```

You can generate any matrix multiplication size using:
```
perl gendata.pl --dimM=128 --dimK=128 --dimN=128 --seed=42 > data_128.in
```
### Simulation sizes 

There are provided 4 different simulation sizes (arguments to run the application).

Whe you are executing an application, it will include the corresopnding argument to run a predefined simsize. The interactive script already includes all those simulation sizes.
#### simtiny 
```
blackscholes_args   = "1 input/in_512.input output_prices.txt"
canneal_args        = "1 100 300 input/100.nets 8"
streamcluster_args  = "3 10 128 128 128 10 none output.txt 1"
swaptions_args      = "-ns 8 -sm 512 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 2 -np 256"
pathfinder_args     = "_pathfinder/input/data_tiny.in"
axpy_args           = "256"
lavaMD_args         = "-cores 1 -boxes1d 1 -outputFile result.txt"
somier_args         = "2 64"
jacobi_2d_args      = "32 2 output.txt"
matmul_args         = "input/data_64.in"
spmv_args           = "input/football.mtx input/football.verif"
```

#### simsmall 
```
blackscholes_args   = "1 input/in_4K.input output_prices.txt"
canneal_args        = "1 10000 2000 input/100000.nets 32"
streamcluster_args  = "10 20 128 4096 4096 1000 none output.txt 1"
swaptions_args      = "-ns 8 -sm 4096 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 8 -np 1024"
pathfinder_args     = "_pathfinder/input/data_small.in"
axpy_args           = "512"
lavaMD_args         = "-cores 1 -boxes1d 4 -outputFile result.txt"
somier_args         = "4 64"
jacobi_2d_args      = "128 10 output.txt"
matmul_args         = "input/data_128.in"
spmv_args           = "input/lhr07.mtx input/lhr07.verif"
```  

#### simmedium
```
blackscholes_args   = "1 input/in_16K.input prices.txt"
canneal_args        = "1 15000 2000 input/200000.nets 64"
streamcluster_args  = "10 20 128 8192 8192 1000 none output.txt 1"
swaptions_args      = "-ns 32 -sm 8192 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 16 -np 4096"
pathfinder_args     = "_pathfinder/input/data_medium.in""
axpy_args           = "1024"
lavaMD_args         = "-cores 1 -boxes1d 6 -outputFile result.txt"
somier_args         = "2 128"
jacobi_2d_args      = "256 100 output.txt"
matmul_args         = "input/data_256.in"
spmv_args           = "input/venkat25.mtx input/venkat25.verif"
```  

#### simlarge
```
blackscholes_args   = "1 input/in_64K.input prices.txt"
canneal_args        = "1 15000 2000 input/400000.nets 128"
streamcluster_args  = "10 20 128 8192 8192 1000 none output.txt 1"
swaptions_args      = "-ns 64 -sm 16384 -nt 1"
particlefilter_args = "-x 128 -y 128 -z 24 -np 8192"
pathfinder_args     = ""_pathfinder/input/data_large.in""
axpy_args           = "2048"
lavaMD_args         = "-cores 1 -boxes1d 10 -outputFile result.txt"
somier_args         = "4 128"
jacobi_2d_args      = "256 2000 output.txt"
matmul_args         = "input/data_512.in"
spmv_args           = "input/poisson3Db.mtx input/poisson3Db.verif"
```  

## Contributing

New vectorized applications are welcome. We strongly encourage you to contribute with new apps to enrich the scenarios and diversity in the RiVEC Bencmark Suite.

## Acknowledgements
We thank the [European Processor Initiative](https://www.european-processor-initiative.eu/) (EPI) project, and the Barcelona Supercomputing Center compiler team, specially to Roger Ferrer who have always support us and solved our doubts about compiler-related issues.

## Contact
Cristobal Ramirez
cristobal.ramirez.lazo@gmail.com
