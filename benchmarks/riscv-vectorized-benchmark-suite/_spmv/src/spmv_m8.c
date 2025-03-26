/*
 * Neiel Israel Leyva Santes
 * neiel.leyva@bsc.es
 * Barcelona Supercomputing Center
 *
 * SpMV Vector Implementation.
 * Sparse Matrix-Vector Multiplication (SpMV) is a mathematical operation
 * in which a sparse matrix is multiplied by a dense vector.
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../../common/riscv_util.h"
#ifdef USE_RISCV_VECTOR
#include <riscv_vector.h>
#include "vector_defines.h"
#endif

#ifdef USE_RISCV_VECTOR

void spmv_intrinsics(const size_t nrows, double *a, uint64_t *ia, uint64_t *ja, double *x, double *y) {

    _MMR_f64 va;
    _MMR_u64 v_idx_row;
    _MMR_f64 vx;
    _MMR_f64 vprod;
    _MMR_f64 part_res;

    for (size_t row = 0; row < nrows; row++) {
        int64_t nnz_row = ia[row + 1] - ia[row];
        int64_t idx     = ia[row];

        if(nnz_row == 0) {
            y[row] = 0;
        } else {
            double sum = 0.0;
            // Temporary Vector
            vfloat64m1_t tmp = __riscv_vfmv_s_f_f64m1(0.0, 1);  // Initialize vector with 0.0
            size_t gvl;

            for(size_t colid = 0; colid < nnz_row; colid += gvl ) {
                gvl = __riscv_vsetvl_e64m8(nnz_row - colid);  // Set vector length dynamically (8 regs - 32 elements)

                vfloat64m8_t val_vec = __riscv_vle64_v_f64m8(&a[idx+colid], gvl); // Load matrix values (8 regs - 32 double)

                vuint64m8_t vec64 = __riscv_vle64_v_u64m8(&ja[idx+colid], gvl); //(4 regs - 32 integer)

                vec64 = __riscv_vsll_vx_u64m8(vec64, 3, gvl); //(4 regs - 32 integer)

                vfloat64m8_t x_vec = __riscv_vluxei64_v_f64m8(x, vec64, gvl); // Gather x values (8 regs - 32 double)

                vfloat64m8_t product = __riscv_vfmul_vv_f64m8(val_vec, x_vec, gvl); // Multiply (8 regs - 32 double)

                // Add partial sum of vec_mul to the cumulative result in vec_accum
                vfloat64m1_t ret_sum = __riscv_vfredosum_vs_f64m8_f64m1(product, tmp, gvl);

                // Extract the scalar result from the accumulated vector
                sum += __riscv_vfmv_f_s_f64m1_f64(ret_sum);

                //va        = _MM_LOAD_f64(&a[idx+colid],  gvl);
                //v_idx_row = _MM_LOAD_u64(&ja[idx+colid], gvl);
                //v_idx_row = _MM_SLL_VX_u64(v_idx_row, 3, gvl);
                //vx        = _MM_LOAD_INDEX_f64(x, v_idx_row, gvl);
                //vprod     = _MM_MACC_f64(vprod,va, vx, gvl);
            }

            y[row] = sum;
//             gvl       = _MMR_VSETVL_E64M1(nnz_row);
//             part_res  = _MM_REDSUM_f64(vprod, part_res, gvl);
//             y[row]    = _MM_VGETFIRST_f64(part_res);
        }
    }
}
#else
void spmv_serial(const size_t nrows, double *a, uint64_t *ia, uint64_t *ja, double *x, double *y) {
    for (int row=0; row<nrows; row++) {
        double sum = 0;
        for (size_t idx=ia[row]; idx<ia[row+1]; idx++){
            sum += a[idx] * x[ja[idx]] ;
        }
        y[row] = sum;
    }
}
#endif
