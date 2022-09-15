/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_M_AIW.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 20-Jul-2022 15:55:09
 */

/* Include Files */
#include "compute_M_AIW.h"
#include "xgetrf.h"

/* Function Definitions */
/*
 * Arguments    : double a11
 *                double a12
 *                double a13
 *                double a14
 *                double a21
 *                double a22
 *                double a23
 *                double a24
 *                double a31
 *                double a32
 *                double a33
 *                double a34
 *                double a41
 *                double a42
 *                double a43
 *                double a44
 *                double i11
 *                double i12
 *                double i13
 *                double i14
 *                double i21
 *                double i22
 *                double i23
 *                double i24
 *                double i31
 *                double i32
 *                double i33
 *                double i34
 *                double i41
 *                double i42
 *                double i43
 *                double i44
 *                double w11
 *                double w12
 *                double w13
 *                double w14
 *                double w21
 *                double w22
 *                double w23
 *                double w24
 *                double w31
 *                double w32
 *                double w33
 *                double w34
 *                double w41
 *                double w42
 *                double w43
 *                double w44
 *                double *m11
 *                double *m12
 *                double *m13
 *                double *m14
 *                double *m21
 *                double *m22
 *                double *m23
 *                double *m24
 *                double *m31
 *                double *m32
 *                double *m33
 *                double *m34
 *                double *m41
 *                double *m42
 *                double *m43
 *                double *m44
 * Return Type  : void
 */
void compute_M_AIW(double a11, double a12, double a13, double a14, double a21,
                   double a22, double a23, double a24, double a31, double a32,
                   double a33, double a34, double a41, double a42, double a43,
                   double a44, double i11, double i12, double i13, double i14,
                   double i21, double i22, double i23, double i24, double i31,
                   double i32, double i33, double i34, double i41, double i42,
                   double i43, double i44, double w11, double w12, double w13,
                   double w14, double w21, double w22, double w23, double w24,
                   double w31, double w32, double w33, double w34, double w41,
                   double w42, double w43, double w44, double *m11, double *m12,
                   double *m13, double *m14, double *m21, double *m22,
                   double *m23, double *m24, double *m31, double *m32,
                   double *m33, double *m34, double *m41, double *m42,
                   double *m43, double *m44)
{
  double A[16];
  double b_I[16];
  double temp;
  int ipiv[4];
  int I_tmp;
  int i;
  int i1;
  int info;
  int j;
  int jBcol;
  int k;
  int kAcol;
  b_I[0] = i11;
  b_I[4] = i12;
  b_I[8] = i13;
  b_I[12] = i14;
  b_I[1] = i21;
  b_I[5] = i22;
  b_I[9] = i23;
  b_I[13] = i24;
  b_I[2] = i31;
  b_I[6] = i32;
  b_I[10] = i33;
  b_I[14] = i34;
  b_I[3] = i41;
  b_I[7] = i42;
  b_I[11] = i43;
  b_I[15] = i44;
  A[0] = a11;
  A[4] = a12;
  A[8] = a13;
  A[12] = a14;
  A[1] = a21;
  A[5] = a22;
  A[9] = a23;
  A[13] = a24;
  A[2] = a31;
  A[6] = a32;
  A[10] = a33;
  A[14] = a34;
  A[3] = a41;
  A[7] = a42;
  A[11] = a43;
  A[15] = a44;
  xgetrf(A, ipiv, &info);
  for (info = 0; info < 3; info++) {
    i = ipiv[info];
    if (i != info + 1) {
      temp = b_I[info];
      b_I[info] = b_I[i - 1];
      b_I[i - 1] = temp;
      temp = b_I[info + 4];
      b_I[info + 4] = b_I[i + 3];
      b_I[i + 3] = temp;
      temp = b_I[info + 8];
      b_I[info + 8] = b_I[i + 7];
      b_I[i + 7] = temp;
      temp = b_I[info + 12];
      b_I[info + 12] = b_I[i + 11];
      b_I[i + 11] = temp;
    }
  }
  for (j = 0; j < 4; j++) {
    jBcol = j << 2;
    for (k = 0; k < 4; k++) {
      kAcol = k << 2;
      i = k + jBcol;
      if (b_I[i] != 0.0) {
        i1 = k + 2;
        for (info = i1; info < 5; info++) {
          I_tmp = (info + jBcol) - 1;
          b_I[I_tmp] -= b_I[i] * A[(info + kAcol) - 1];
        }
      }
    }
  }
  for (j = 0; j < 4; j++) {
    jBcol = j << 2;
    for (k = 3; k >= 0; k--) {
      kAcol = k << 2;
      i = k + jBcol;
      temp = b_I[i];
      if (temp != 0.0) {
        b_I[i] = temp / A[k + kAcol];
        for (info = 0; info < k; info++) {
          I_tmp = info + jBcol;
          b_I[I_tmp] -= b_I[i] * A[info + kAcol];
        }
      }
    }
  }
  A[0] = w11;
  A[4] = w12;
  A[8] = w13;
  A[12] = w14;
  A[1] = w21;
  A[5] = w22;
  A[9] = w23;
  A[13] = w24;
  A[2] = w31;
  A[6] = w32;
  A[10] = w33;
  A[14] = w34;
  A[3] = w41;
  A[7] = w42;
  A[11] = w43;
  A[15] = w44;
  xgetrf(A, ipiv, &info);
  for (j = 0; j < 4; j++) {
    info = j << 2;
    for (k = 0; k < j; k++) {
      jBcol = k << 2;
      temp = A[k + info];
      if (temp != 0.0) {
        b_I[info] -= temp * b_I[jBcol];
        b_I[info + 1] -= temp * b_I[jBcol + 1];
        b_I[info + 2] -= temp * b_I[jBcol + 2];
        b_I[info + 3] -= temp * b_I[jBcol + 3];
      }
    }
    temp = 1.0 / A[j + info];
    b_I[info] *= temp;
    b_I[info + 1] *= temp;
    b_I[info + 2] *= temp;
    b_I[info + 3] *= temp;
  }
  for (j = 3; j >= 0; j--) {
    info = (j << 2) - 1;
    i = j + 2;
    for (k = i; k < 5; k++) {
      jBcol = (k - 1) << 2;
      temp = A[k + info];
      if (temp != 0.0) {
        b_I[info + 1] -= temp * b_I[jBcol];
        b_I[info + 2] -= temp * b_I[jBcol + 1];
        b_I[info + 3] -= temp * b_I[jBcol + 2];
        b_I[info + 4] -= temp * b_I[jBcol + 3];
      }
    }
  }
  for (j = 2; j >= 0; j--) {
    i = ipiv[j];
    if (i != j + 1) {
      info = j << 2;
      temp = b_I[info];
      I_tmp = (i - 1) << 2;
      b_I[info] = b_I[I_tmp];
      b_I[I_tmp] = temp;
      temp = b_I[info + 1];
      b_I[info + 1] = b_I[I_tmp + 1];
      b_I[I_tmp + 1] = temp;
      temp = b_I[info + 2];
      b_I[info + 2] = b_I[I_tmp + 2];
      b_I[I_tmp + 2] = temp;
      temp = b_I[info + 3];
      b_I[info + 3] = b_I[I_tmp + 3];
      b_I[I_tmp + 3] = temp;
    }
  }
  *m11 = b_I[0];
  *m12 = b_I[4];
  *m13 = b_I[8];
  *m14 = b_I[12];
  *m21 = b_I[1];
  *m22 = b_I[5];
  *m23 = b_I[9];
  *m24 = b_I[13];
  *m31 = b_I[2];
  *m32 = b_I[6];
  *m33 = b_I[10];
  *m34 = b_I[14];
  *m41 = b_I[3];
  *m42 = b_I[7];
  *m43 = b_I[11];
  *m44 = b_I[15];
}

/*
 * File trailer for compute_M_AIW.c
 *
 * [EOF]
 */
