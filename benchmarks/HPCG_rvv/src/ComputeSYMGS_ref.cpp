
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
// ***************************************************
//@HEADER

/*!
 @file ComputeSYMGS_ref.cpp

 HPCG routine
 */

#ifndef HPCG_NO_MPI
#include "ExchangeHalo.hpp"
#endif
#include "ComputeSYMGS_ref.hpp"
#include <cassert>

#define RVV

#ifdef RVV
#include <riscv_vector.h> // Ensure to include RISC-V vector header
#endif

/*!
  Computes one step of symmetric Gauss-Seidel:

  Assumption about the structure of matrix A:
  - Each row 'i' of the matrix has nonzero diagonal value whose address is matrixDiagonal[i]
  - Entries in row 'i' are ordered such that:
       - lower triangular terms are stored before the diagonal element.
       - upper triangular terms are stored after the diagonal element.
       - No other assumptions are made about entry ordering.

  Symmetric Gauss-Seidel notes:
  - We use the input vector x as the RHS and start with an initial guess for y of all zeros.
  - We perform one forward sweep.  x should be initially zero on the first GS sweep, but we do not attempt to exploit this fact.
  - We then perform one back sweep.
  - For simplicity we include the diagonal contribution in the for-j loop, then correct the sum after

  @param[in] A the known system matrix
  @param[in] r the input vector
  @param[inout] x On entry, x should contain relevant values, on exit x contains the result of one symmetric GS sweep with r as the RHS.


  @warning Early versions of this kernel (Version 1.1 and earlier) had the r and x arguments in reverse order, and out of sync with other kernels.

  @return returns 0 upon success and non-zero otherwise

  @see ComputeSYMGS
*/
int ComputeSYMGS_ref( const SparseMatrix & A, const Vector & r, Vector & x) {

  assert(x.localLength==A.localNumberOfColumns); // Make sure x contain space for halo values

#ifndef HPCG_NO_MPI
  ExchangeHalo(A,x);
#endif

  const local_int_t nrow = A.localNumberOfRows;
  double ** matrixDiagonal = A.matrixDiagonal;  // An array of pointers to the diagonal entries A.matrixValues
  const double * const rv = r.values;
  double * const xv = x.values;

#ifndef RVV


  for (local_int_t i=0; i< nrow; i++) {
    const double * const currentValues = A.matrixValues[i];
    const local_int_t * const currentColIndices = A.mtxIndL[i];
    const int currentNumberOfNonzeros = A.nonzerosInRow[i];
    const double  currentDiagonal = matrixDiagonal[i][0]; // Current diagonal value
    double sum = rv[i]; // RHS value

    for (int j=0; j< currentNumberOfNonzeros; j++) {
      local_int_t curCol = currentColIndices[j];
      sum -= currentValues[j] * xv[curCol];
    }
    sum += xv[i]*currentDiagonal; // Remove diagonal contribution from previous loop

    xv[i] = sum/currentDiagonal;

  }

  // Now the back sweep.

  for (local_int_t i=nrow-1; i>=0; i--) {
    const double * const currentValues = A.matrixValues[i];
    const local_int_t * const currentColIndices = A.mtxIndL[i];
    const int currentNumberOfNonzeros = A.nonzerosInRow[i];
    const double  currentDiagonal = matrixDiagonal[i][0]; // Current diagonal value
    double sum = rv[i]; // RHS value

    for (int j = 0; j< currentNumberOfNonzeros; j++) {
      local_int_t curCol = currentColIndices[j];
      sum -= currentValues[j]*xv[curCol];
    }
    sum += xv[i]*currentDiagonal; // Remove diagonal contribution from previous loop

    xv[i] = sum/currentDiagonal;
  }

#else

  for (local_int_t i=0; i< nrow; i++) {
    const double * const currentValues = A.matrixValues[i];
    const uint32_t * const currentColIndices = (uint32_t *) A.mtxIndL[i];
    const int currentNumberOfNonzeros = A.nonzerosInRow[i];
    const double  currentDiagonal = matrixDiagonal[i][0]; // Current diagonal value
    double sum = rv[i]; // RHS value

    // Temporary Vector
    vfloat64m1_t tmp = __riscv_vfmv_s_f_f64m1(0.0, 1);  // Initialize vector with 0.0

    size_t vl;

    for (int j = 0; j < currentNumberOfNonzeros; j += vl) {
            vl = __riscv_vsetvl_e64m8(currentNumberOfNonzeros - j);  // Set vector length dynamically (4 regs - 16 elements)

            vuint32m4_t vec32 = __riscv_vle32_v_u32m4(&currentColIndices[j], vl); //(4 regs - 32 integer)

            vec32 = __riscv_vsll_vx_u32m4(vec32, 3, vl); //(4 regs - 32 integer)

            vfloat64m8_t x_vec = __riscv_vluxei32_v_f64m8(xv, vec32, vl); // Gather x values (8 regs - 32 double)

            vfloat64m8_t val_vec = __riscv_vle64_v_f64m8(&currentValues[j], vl); // Load matrix values (8 regs - 32 double)

            vfloat64m8_t product = __riscv_vfmul_vv_f64m8(val_vec, x_vec, vl); // Multiply (8 regs - 32 double)

            // Add partial sum of vec_mul to the cumulative result in vec_accum
            vfloat64m1_t ret_sum = __riscv_vfredosum_vs_f64m8_f64m1(product, tmp, vl);

            // Extract the scalar result from the accumulated vector
            sum -= __riscv_vfmv_f_s_f64m1_f64(ret_sum);
    }


    sum += xv[i]*currentDiagonal; // Remove diagonal contribution from previous loop

    xv[i] = sum/currentDiagonal;

  }

  // Now the back sweep.

  for (local_int_t i=nrow-1; i>=0; i--) {
    const double * const currentValues = A.matrixValues[i];
    const uint32_t * const currentColIndices = (uint32_t *) A.mtxIndL[i];
    const int currentNumberOfNonzeros = A.nonzerosInRow[i];
    const double  currentDiagonal = matrixDiagonal[i][0]; // Current diagonal value
    double sum = rv[i]; // RHS value


    // Temporary Vector
    vfloat64m1_t tmp = __riscv_vfmv_s_f_f64m1(0.0, 1);  // Initialize vector with 0.0

    size_t vl;

    for (int j = 0; j < currentNumberOfNonzeros; j += vl) {
            vl = __riscv_vsetvl_e64m8(currentNumberOfNonzeros - j);  // Set vector length dynamically (4 regs - 16 elements)

            vuint32m4_t vec32 = __riscv_vle32_v_u32m4(&currentColIndices[j], vl); //(4 regs - 32 integer)

            vec32 = __riscv_vsll_vx_u32m4(vec32, 3, vl); //(4 regs - 32 integer)

            vfloat64m8_t x_vec = __riscv_vluxei32_v_f64m8(xv, vec32, vl); // Gather x values (8 regs - 32 double)

            vfloat64m8_t val_vec = __riscv_vle64_v_f64m8(&currentValues[j], vl); // Load matrix values (8 regs - 32 double)

            vfloat64m8_t product = __riscv_vfmul_vv_f64m8(val_vec, x_vec, vl); // Multiply (8 regs - 32 double)

            // Add partial sum of vec_mul to the cumulative result in vec_accum
            vfloat64m1_t ret_sum = __riscv_vfredosum_vs_f64m8_f64m1(product, tmp, vl);

            // Extract the scalar result from the accumulated vector
            sum -= __riscv_vfmv_f_s_f64m1_f64(ret_sum);
    }

    sum += xv[i]*currentDiagonal; // Remove diagonal contribution from previous loop

    xv[i] = sum/currentDiagonal;
  }

#endif

  return 0;
}
