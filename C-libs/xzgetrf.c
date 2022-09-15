/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzgetrf.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Jul-2022 12:50:42
 */

/* Include Files */
#include "xzgetrf.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : double A[16]
 *                int ipiv[4]
 *                int *info
 * Return Type  : void
 */
void xzgetrf(double A[16], int ipiv[4], int *info)
{
  double s;
  double smax;
  int b_tmp;
  int i;
  int j;
  int jA;
  int jp1j;
  int k;
  int mmj_tmp;
  int n;
  ipiv[0] = 1;
  ipiv[1] = 2;
  ipiv[2] = 3;
  ipiv[3] = 4;
  *info = 0;
  for (j = 0; j < 3; j++) {
    mmj_tmp = 2 - j;
    b_tmp = j * 5;
    jp1j = b_tmp + 2;
    n = 4 - j;
    jA = 0;
    smax = fabs(A[b_tmp]);
    for (k = 2; k <= n; k++) {
      s = fabs(A[(b_tmp + k) - 1]);
      if (s > smax) {
        jA = k - 1;
        smax = s;
      }
    }
    if (A[b_tmp + jA] != 0.0) {
      if (jA != 0) {
        n = j + jA;
        ipiv[j] = n + 1;
        smax = A[j];
        A[j] = A[n];
        A[n] = smax;
        smax = A[j + 4];
        A[j + 4] = A[n + 4];
        A[n + 4] = smax;
        smax = A[j + 8];
        A[j + 8] = A[n + 8];
        A[n + 8] = smax;
        smax = A[j + 12];
        A[j + 12] = A[n + 12];
        A[n + 12] = smax;
      }
      i = (b_tmp - j) + 4;
      for (n = jp1j; n <= i; n++) {
        A[n - 1] /= A[b_tmp];
      }
    } else {
      *info = j + 1;
    }
    jA = b_tmp;
    for (jp1j = 0; jp1j <= mmj_tmp; jp1j++) {
      n = (b_tmp + (jp1j << 2)) + 4;
      smax = A[n];
      if (A[n] != 0.0) {
        i = jA + 6;
        n = (jA - j) + 8;
        for (k = i; k <= n; k++) {
          A[k - 1] += A[((b_tmp + k) - jA) - 5] * -smax;
        }
      }
      jA += 4;
    }
  }
  if ((*info == 0) && (!(A[15] != 0.0))) {
    *info = 4;
  }
}

/*
 * File trailer for xzgetrf.c
 *
 * [EOF]
 */
