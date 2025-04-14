########################################################
# RVV-enabled High Performance Conjugate Gradient Benchmark (HPCG) #
########################################################

Jack Dongarra and Michael Heroux and Piotr Luszczek

Revision: 3.1

Date: April 15, 2025

## Introduction ##

This fork of HPCG integrates support for the RISC-V Vector Extension (RVV) 1.0 to accelerate core computational routines on RISC-V hardware. RVV is a powerful vector extension that allows for scalable data-level parallelism across different implementations, and we've leveraged it to optimize the most compute-intensive parts of the benchmark. 
To maximize vector throughput and take advantage of wider vector registers, we use LMUL=8 across all vectorized routines. This setting allows for greater performance when the hardware supports large vector lengths, which is especially beneficial for workloads dominated by streaming and sparse linear algebra operations. These changes maintain compatibility with the original algorithmic behavior of HPCG while delivering significantly improved performance on RVV-enabled processors. 


### RVV 1.0 Optimized Kernels

The following computational kernels have been optimized using RISC-V Vector Extension (RVV) 1.0 intrinsics. All implementations use LMUL=8 for improved performance on supported hardware.

| File Name                     | Description                                  | RVV Optimization | LMUL Used |
|------------------------------|----------------------------------------------|------------------|-----------|
| ComputeDotProduct_ref.cpp    | Parallel dot product of two vectors          | Yes              | 8         |
| ComputeProlongation_ref.cpp  | Prolongation operator (interpolation)        | Yes              | 8         |
| ComputeRestriction_ref.cpp   | Restriction operator (coarse grid transfer)  | Yes              | 8         |
| ComputeSYMGS_ref.cpp         | Symmetric Gauss-Seidel smoothing             | Yes              | 8         |
| ComputeWAXPBY_ref.cpp        | Linear combination of vectors (WAXPBY)       | Yes              | 8         |

The official HPCG GitHub: https://github.com/hpcg-benchmark/hpcg

## Installation ##

To compile the RVV-optimized version of HPCG, a custom Makefile named Make.Linux_MPI_RVV has been provided under setup/. This configuration enables RVV 1.0 support along with MPI for parallel execution on RISC-V platforms.

To compile the RVV-optimized version of HPCG, a custom Makefile named `Make.Linux_MPI_RVV` is provided under `setup/`. This configuration enables RVV 1.0 support along with MPI for parallel execution on RISC-V platforms.

Run the following commands to build:

```bash
cd benchmarks/HPCG_rvv/
mkdir build
cd build
../configure Linux_MPI_RVV
make -j```

## Execution ##

You can execute the HPCG using:

```
cd benchmarks/HPCG_rvv/
mpirun -n 8 build/bin/xhpcg --nx=16 --ny=16 --nz=16 --npx=2 --npy=2 --npz=2 --rt=1
```

