/*************************************************************************
* Vectorized Axpy Kernel
* Author: Jesus Labarta
* Barcelona Supercomputing Center
*************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#ifdef USE_RISCV_VECTOR
#include <riscv_vector.h>
#include "../../common/vector_defines.h"
#endif

#ifndef USE_RISCV_VECTOR

void axpy_serial(double a, double *dx, double *dy, int n) {
   int i;
   for (i=0; i<n; i++) {
      dy[i] += a*dx[i];
   }
}

#else

void axpy_vector(double a, double *dx, double *dy, int n) {
  int i;

  long gvl = __riscv_vsetvl_e64m8(n);

  for (i = 0; i < n;) {
    gvl = __riscv_vsetvl_e64m8(n - i);
    vfloat64m8_t v_dx = __riscv_vle64_v_f64m8(&dx[i], gvl);
    vfloat64m8_t v_dy = __riscv_vle64_v_f64m8(&dy[i], gvl);
    vfloat64m8_t v_res = __riscv_vfmacc_vf_f64m8(v_dy, a, v_dx, gvl);
    __riscv_vse64_v_f64m8(&dy[i], v_res, gvl);

    i += gvl;
  }
}

#endif
