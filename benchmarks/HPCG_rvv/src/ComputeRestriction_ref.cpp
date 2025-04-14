
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
 @file ComputeRestriction_ref.cpp

 HPCG routine
 */


#ifndef HPCG_NO_OPENMP
#include <omp.h>
#endif

#include "ComputeRestriction_ref.hpp"

#define RVV

#ifdef RVV
#include <riscv_vector.h> // Ensure to include RISC-V vector header
#endif

/*!
  Routine to compute the coarse residual vector.

  @param[inout]  A - Sparse matrix object containing pointers to mgData->Axf, the fine grid matrix-vector product and mgData->rc the coarse residual vector.
  @param[in]    rf - Fine grid RHS.


  Note that the fine grid residual is never explicitly constructed.
  We only compute it for the fine grid points that will be injected into corresponding coarse grid points.

  @return Returns zero on success and a non-zero value otherwise.
*/
int ComputeRestriction_ref(const SparseMatrix & A, const Vector & rf) {

  double * Axfv = A.mgData->Axf->values;
  double * rfv = rf.values;
  double * rcv = A.mgData->rc->values;
  uint32_t * f2c = (uint32_t *) A.mgData->f2cOperator;
  local_int_t nc = A.mgData->rc->localLength;

#ifndef HPCG_NO_OPENMP
#pragma omp parallel for
#endif

#ifndef RVV
  for (local_int_t i=0; i<nc; ++i) rcv[i] = rfv[f2c[i]] - Axfv[f2c[i]];
#else

        size_t vl;
        for (int i = 0; i < nc; i += vl) {
            vl = __riscv_vsetvl_e64m8(nc - i);  // Set vector length dynamically (8 regs - 32 elements)

            vuint32m4_t vec32 = __riscv_vle32_v_u32m4(&f2c[i], vl); //(4 regs - 32 integer)

            vec32 = __riscv_vsll_vx_u32m4(vec32, 3, vl); //(4 regs - 32 integer)

            vfloat64m8_t rfv_vec = __riscv_vluxei32_v_f64m8(rfv, vec32, vl); // Gather rfv values (8 regs - 32 double)

            vfloat64m8_t Axfv_vec = __riscv_vluxei32_v_f64m8(Axfv, vec32, vl); // Gather Axfv values (8 regs - 32 double)

            // Compute element-wise difference: rfv - Axfv.
            vfloat64m8_t result =  __riscv_vfsub_vv_f64m8(rfv_vec, Axfv_vec, vl);

            // Store the result into the contiguous rcv array.
             __riscv_vse64_v_f64m8(&rcv[i], result, vl);

        }

#endif



  return 0;
}
