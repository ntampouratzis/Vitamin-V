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

See the file `INSTALL` in this directory.

## Valid Runs ##

HPCG can be run in just a few minutes from start to finish.  However, official
runs must be at least 1800 seconds (30 minutes) as reported in the output file.
The Quick Path option is an exception for machines that are in production mode
prior to broad availability of an optimized version of HPCG 3.0 for a given platform.
In this situation (which should be confirmed by sending a note to the HPCG Benchmark
owners) the Quick Path option can be invoked by setting the run time parameter equal
to 0 (zero).

A valid run must also execute a problem size that is large enough so that data
arrays accessed in the CG iteration loop do not fit in the cache of the device
in a way that would be unrealistic in a real application setting.  Presently this
restriction means that the problem size should be large enough to occupy a
significant fraction of *main memory*, at least 1/4 of the total.

Future memory system architectures may require restatement of the specific memory
size requirements.  But the guiding principle will always be that the problem
size should reflect what would be reasonable for a real sparse iterative solver.

## Documentation ##

The source code documentation can be generated with a Doxygen (version 1.8 or
newer). In this directory type:

    doxygen tools/hpcg.dox

Doxygen will then generate various output formats in the `out` directory.

## Tuning ##

See the file `TUNING` in this directory.

## Bugs ##

Known problems and bugs with this release are documented in the file
`BUGS`.

## Further information ##

Check out  the website  http://www.hpcg-benchmark.org/ for the latest
information and performance results.
