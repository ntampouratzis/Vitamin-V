
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
 @file ComputeProlongation_ref.cpp

 HPCG routine
 */

#ifndef HPCG_NO_OPENMP
#include <omp.h>
#endif

#include "ComputeProlongation_ref.hpp"

#define RVV

#ifdef RVV
#include <riscv_vector.h> // Ensure to include RISC-V vector header
#endif

/*!
  Routine to compute the coarse residual vector.

  @param[in]  Af - Fine grid sparse matrix object containing pointers to current coarse grid correction and the f2c operator.
  @param[inout] xf - Fine grid solution vector, update with coarse grid correction.

  Note that the fine grid residual is never explicitly constructed.
  We only compute it for the fine grid points that will be injected into corresponding coarse grid points.

  @return Returns zero on success and a non-zero value otherwise.
*/
int ComputeProlongation_ref(const SparseMatrix & Af, Vector & xf) {

  double * xfv = xf.values;
  double * xcv = Af.mgData->xc->values;
  uint32_t * f2c = (uint32_t *) Af.mgData->f2cOperator;
  local_int_t nc = Af.mgData->rc->localLength;

#ifndef HPCG_NO_OPENMP
#pragma omp parallel for
#endif
// TODO: Somehow note that this loop can be safely vectorized since f2c has no repeated indices
#ifndef RVV
  for (local_int_t i=0; i<nc; ++i) xfv[f2c[i]] += xcv[i]; // This loop is safe to vectorize
#else

        size_t vl;
        for (int i = 0; i < nc; i += vl) {
            vl = __riscv_vsetvl_e64m8(nc - i);  // Set vector length dynamically (8 regs - 32 elements)

            vuint32m4_t vec32 = __riscv_vle32_v_u32m4(&f2c[i], vl); //(4 regs - 32 integer)

            vec32 = __riscv_vsll_vx_u32m4(vec32, 3, vl); //(4 regs - 32 integer)

            vfloat64m8_t xfv_vec_old = __riscv_vluxei32_v_f64m8(xfv, vec32, vl); // Gather xfv values (8 regs - 32 double)

            vfloat64m8_t xcv_vec = __riscv_vle64_v_f64m8(&xcv[i], vl); // Load matrix values (8 regs - 32 double)

            // Compute the updated values: xfv_vec_old + xcv_vec.
            vfloat64m8_t updated =  __riscv_vfadd_vv_f64m8(xfv_vec_old, xcv_vec, vl);

            // Scatter store the updated values back to xfv using the same indices.
            __riscv_vsoxei32_v_f64m8(xfv, vec32, updated, vl);

        }

#endif
  return 0;
}
