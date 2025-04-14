//@HEADER
// ***************************************************
//
// HPCG: High Performance Conjugate Gradient Benchmark
//
// Contact:
// Michael A. Heroux ( maherou@sandia.gov)
// Jack Dongarra     (dongarra@eecs.utk.edu)
// Piotr Luszczek    (luszczek@eecs.utk.edu)
//
// RVV: Nikolaos Tampouratzis (ntampouratzis@ihu.gr)
// ***************************************************
//@HEADER

/*!
 @file ComputeDotProduct_ref.cpp

 HPCG routine RVV
 */

#ifndef HPCG_NO_MPI
#include <mpi.h>
#include "mytimer.hpp"
#endif
#ifndef HPCG_NO_OPENMP
#include <omp.h>
#endif
#include <cassert>
#include "ComputeDotProduct_ref.hpp"

#define RVV


#ifdef RVV
#include <riscv_vector.h> // Ensure to include RISC-V vector header
#endif

/*!
  Routine to compute the dot product of two vectors where:

  This is the reference dot-product implementation.  It _CANNOT_ be modified for the
  purposes of this benchmark.

  @param[in] n the number of vector elements (on this processor)
  @param[in] x, y the input vectors
  @param[in] result a pointer to scalar value, on exit will contain result.
  @param[out] time_allreduce the time it took to perform the communication between processes

  @return returns 0 upon success and non-zero otherwise

  @see ComputeDotProduct
*/
int ComputeDotProduct_ref(const local_int_t n, const Vector & x, const Vector & y,
    double & result, double & time_allreduce) {
  assert(x.localLength>=n); // Test vector lengths
  assert(y.localLength>=n);

  double local_result = 0.0;
  double * xv = x.values;
  double * yv = y.values;

#ifndef RVV

  if (yv==xv) {
#ifndef HPCG_NO_OPENMP
    #pragma omp parallel for reduction (+:local_result)
#endif
    for (local_int_t i=0; i<n; i++) local_result += xv[i]*xv[i];
  } else {
#ifndef HPCG_NO_OPENMP
    #pragma omp parallel for reduction (+:local_result)
#endif
    for (local_int_t i=0; i<n; i++) local_result += xv[i]*yv[i];
  }

#endif


#ifdef RVV

	size_t vlmax = __riscv_vsetvlmax_e64m8();

	// Temporary Vector
    vfloat64m8_t vec_accum = __riscv_vfmv_s_f_f64m8(0.0, vlmax);  // Initialize vector with 0.0

    size_t vl;
    vfloat64m8_t vec_xv, vec_yv;
	// Check if both vectors point to the same location
    if (xv == yv) {
		// Vectorized computation using RVV
		for (int i = 0; i < n; i += vl) {
			// Set vector length for remaining elements
			vl = __riscv_vsetvl_e64m8(n - i);

			// Load xv elements into vector registers
			vec_xv = __riscv_vle64_v_f64m8(&xv[i], vl);

            // Perform fused multiply-accumulate: vec_accum += vec_xv * vec_xv
            vec_accum = __riscv_vfmacc_vv_f64m8(vec_accum, vec_xv, vec_xv, vl);
		}
	} else {
		// Vectorized computation using RVV
		for (int i = 0; i < n; i += vl) {
			// Set vector length for remaining elements
			vl = __riscv_vsetvl_e64m8(n - i);

			// Load xv and yv elements into vector registers
			vec_xv = __riscv_vle64_v_f64m8(&xv[i], vl);
			vec_yv = __riscv_vle64_v_f64m8(&yv[i], vl);

            // Perform fused multiply-accumulate: vec_accum += vec_xv * vec_yv
            vec_accum = __riscv_vfmacc_vv_f64m8(vec_accum, vec_xv, vec_yv, vl);
		}
	}

    vfloat64m1_t vec_zero = __riscv_vfmv_v_f_f64m1(0, vlmax);
	vfloat64m1_t vec_sum = __riscv_vfredusum_vs_f64m8_f64m1(vec_accum, vec_zero, vlmax);
    local_result = __riscv_vfmv_f_s_f64m1_f64(vec_sum);

#endif

#ifndef HPCG_NO_MPI
  // Use MPI's reduce function to collect all partial sums
  double t0 = mytimer();
  double global_result = 0.0;
  MPI_Allreduce(&local_result, &global_result, 1, MPI_DOUBLE, MPI_SUM,
      MPI_COMM_WORLD);
  result = global_result;
  time_allreduce += mytimer() - t0;
#else
  time_allreduce += 0.0;
  result = local_result;
#endif

  return 0;
}
