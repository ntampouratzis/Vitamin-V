/*************************************************************************
* Vectorized matrixmul Kernel
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

#define DATA_TYPE 
typedef double data_t;

#ifdef USE_RISCV_VECTOR
#include <riscv_vector.h>
#include "../../common/vector_defines.h"

void matrixmul_intrinsics(data_t *a, data_t *b, data_t *c, data_t *b_T, int n, int m, int p) {

    // Step 1: Compute transposed B (b_T has shape [n][p])
    for (int i = 0; i < p; ++i) {
        for (int j = 0; j < n; ++j) {
            b_T[j * p + i] = b[i * n + j];
        }
    }

    // Step 2: Main multiplication using unit-stride loads
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {
            size_t gvl = __riscv_vsetvl_e64m8(p);
            vfloat64m8_t vprod = __riscv_vfmv_v_f_f64m8(0.0, gvl);
            size_t gvl_m1 = __riscv_vsetvl_e64m1(p);
            vfloat64m1_t vec_zero = __riscv_vfmv_v_f_f64m1(0.0, gvl_m1);

            for (size_t k = 0; k < p; k += gvl) {
                gvl = __riscv_vsetvl_e64m8(p - k);

                // Load a row from A: a[i][k ... k+gvl]
                vfloat64m8_t va = __riscv_vle64_v_f64m8(&a[i * p + k], gvl);

                // Load transposed row from b_T: b_T[j][k ... k+gvl] => now unit-stride
                vfloat64m8_t vb = __riscv_vle64_v_f64m8(&b_T[j * p + k], gvl);

                // Multiply and accumulate
                vprod = __riscv_vfmacc_vv_f64m8(vprod, va, vb, gvl);
            }

            gvl = __riscv_vsetvl_e64m8(p);
            vfloat64m1_t vec_sum  = __riscv_vfredusum_vs_f64m8_f64m1(vprod, vec_zero, gvl);
            c[i * n + j] = __riscv_vfmv_f_s_f64m1_f64(vec_sum);
        }
    }
}


#else // !USE_RISCV_VECTOR

void matmul_serial(data_t *a, data_t *b, data_t *c, int n, int m, int p) {
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            c[i * n + j] = 0;
            for (int k = 0; k < p; ++k) {
                c[i * n + j] += a[i * p + k] * b[k * n + j];
            }
        }
}

#endif


bool compare( size_t dm, size_t dn, data_t *a ,data_t *b) {
    bool result = false;
    for (int i = 0; i < dm; i++) {
        for (int j = 0; j < dn; j++) {
            if(a[i*dn+j] != b[i*dn+j]) {
              result = true;
            }
        }
 
    }
    return result;
}
