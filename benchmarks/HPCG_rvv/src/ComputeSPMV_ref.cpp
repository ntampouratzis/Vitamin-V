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
//
// RVV: Nikolaos Tampouratzis (ntampouratzis@ihu.gr)
// ***************************************************
//@HEADER

/*!
 @file ComputeSPMV_ref.cpp

 HPCG routine
 */

#include "ComputeSPMV_ref.hpp"

#ifndef HPCG_NO_MPI
#include "ExchangeHalo.hpp"
#endif

#ifndef HPCG_NO_OPENMP
#include <omp.h>
#endif
#include <cassert>


#define RVV

#ifdef RVV
#include <riscv_vector.h> // Ensure to include RISC-V vector header
#endif


/*!
  Routine to compute matrix vector product y = Ax where:
  Precondition: First call exchange_externals to get off-processor values of x

  This is the reference SPMV implementation.  It CANNOT be modified for the
  purposes of this benchmark.

  @param[in]  A the known system matrix
  @param[in]  x the known vector
  @param[out] y the On exit contains the result: Ax.

  @return returns 0 upon success and non-zero otherwise

  @see ComputeSPMV
*/
int ComputeSPMV_ref( const SparseMatrix & A, Vector & x, Vector & y) {

  assert(x.localLength>=A.localNumberOfColumns); // Test vector lengths
  assert(y.localLength>=A.localNumberOfRows);

#ifndef HPCG_NO_MPI
    ExchangeHalo(A,x);
#endif
  const double * const xv = x.values;
  double * const yv = y.values;
  const local_int_t nrow = A.localNumberOfRows;


#ifndef HPCG_NO_OPENMP
  #pragma omp parallel for
#endif


#ifndef RVV

  for (local_int_t i=0; i< nrow; i++)  {
    double sum = 0.0;
    const double * const cur_vals = A.matrixValues[i];
    const local_int_t * const cur_inds = A.mtxIndL[i];
    const int cur_nnz = A.nonzerosInRow[i];

    for (int j=0; j< cur_nnz; j++)
      sum += cur_vals[j]*xv[cur_inds[j]];
    yv[i] = sum;
  }

#else

for (local_int_t i = 0; i < nrow; i++) {
        double sum = 0.0;
        const double *cur_vals = A.matrixValues[i];
        const uint32_t *cur_inds = (uint32_t *) A.mtxIndL[i];
        const int cur_nnz = A.nonzerosInRow[i];


        // Temporary Vector
        vfloat64m1_t tmp = __riscv_vfmv_s_f_f64m1(0.0, 1);  // Initialize vector with 0.0

        size_t vl;
        for (int j = 0; j < cur_nnz; j += vl) {
            vl = __riscv_vsetvl_e64m8(cur_nnz - j);  // Set vector length dynamically (8 regs - 32 elements)

            vuint32m4_t vec32 = __riscv_vle32_v_u32m4(&cur_inds[j], vl); //(4 regs - 32 integer)

            vec32 = __riscv_vsll_vx_u32m4(vec32, 3, vl); //(4 regs - 32 integer)

            vfloat64m8_t x_vec = __riscv_vluxei32_v_f64m8(xv, vec32, vl); // Gather x values (8 regs - 32 double)

            vfloat64m8_t val_vec = __riscv_vle64_v_f64m8(&cur_vals[j], vl); // Load matrix values (8 regs - 32 double)

            vfloat64m8_t product = __riscv_vfmul_vv_f64m8(val_vec, x_vec, vl); // Multiply (8 regs - 32 double)

            // Add partial sum of vec_mul to the cumulative result in vec_accum
            vfloat64m1_t ret_sum = __riscv_vfredosum_vs_f64m8_f64m1(product, tmp, vl);

            // Extract the scalar result from the accumulated vector
            sum += __riscv_vfmv_f_s_f64m1_f64(ret_sum);
        }
        yv[i] = sum;
    }

#endif

  return 0;
}
