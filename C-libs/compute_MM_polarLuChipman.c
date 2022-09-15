/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_MM_polarLuChipman.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Jul-2022 12:50:42
 */

/* Include Files */
#include "compute_MM_polarLuChipman.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include "xzgetrf.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double m11
 *                double m12
 *                double m13
 *                double m14
 *                double m21
 *                double m22
 *                double m23
 *                double m24
 *                double m31
 *                double m32
 *                double m33
 *                double m34
 *                double m41
 *                double m42
 *                double m43
 *                double m44
 *                double *t11
 *                double *t12
 *                double *t13
 *                double *t14
 *                double *t21
 *                double *t22
 *                double *t23
 *                double *t24
 *                double *t31
 *                double *t32
 *                double *t33
 *                double *t34
 *                double *t41
 *                double *t42
 *                double *t43
 *                double *t44
 *                double *p11
 *                double *p12
 *                double *p13
 *                double *p14
 *                double *p21
 *                double *p22
 *                double *p23
 *                double *p24
 *                double *p31
 *                double *p32
 *                double *p33
 *                double *p34
 *                double *p41
 *                double *p42
 *                double *p43
 *                double *p44
 *                double *d11
 *                double *d12
 *                double *d13
 *                double *d14
 *                double *d21
 *                double *d22
 *                double *d23
 *                double *d24
 *                double *d31
 *                double *d32
 *                double *d33
 *                double *d34
 *                double *d41
 *                double *d42
 *                double *d43
 *                double *d44
 * Return Type  : void
 */
void compute_MM_polarLuChipman(
    double m11, double m12, double m13, double m14, double m21, double m22,
    double m23, double m24, double m31, double m32, double m33, double m34,
    double m41, double m42, double m43, double m44, double *t11, double *t12,
    double *t13, double *t14, double *t21, double *t22, double *t23,
    double *t24, double *t31, double *t32, double *t33, double *t34,
    double *t41, double *t42, double *t43, double *t44, double *p11,
    double *p12, double *p13, double *p14, double *p21, double *p22,
    double *p23, double *p24, double *p31, double *p32, double *p33,
    double *p34, double *p41, double *p42, double *p43, double *p44,
    double *d11, double *d12, double *d13, double *d14, double *d21,
    double *d22, double *d23, double *d24, double *d31, double *d32,
    double *d33, double *d34, double *d41, double *d42, double *d43,
    double *d44)
{
  static const signed char b[9] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  double M[16];
  double MD[16];
  double M_0[16];
  double Mdelta[16];
  double U[9];
  double V[9];
  double b_D1[9];
  double dvec[3];
  double D;
  double D1;
  double D1_tmp;
  double d;
  int ipiv[4];
  int MD_tmp;
  int i;
  int j;
  int k;
  int kBcol;
  signed char b_b[9];
  boolean_T isodd;
  M[0] = m11;
  M[4] = m12;
  M[8] = m13;
  M[12] = m14;
  M[1] = m21;
  M[5] = m22;
  M[9] = m23;
  M[13] = m24;
  M[2] = m31;
  M[6] = m32;
  M[10] = m33;
  M[14] = m34;
  M[3] = m41;
  M[7] = m42;
  M[11] = m43;
  M[15] = m44;
  /*  Diattenualtion Matrix  */
  D = 1.0 / m11;
  dvec[0] = m12 * D;
  dvec[1] = m13 * D;
  dvec[2] = m14 * D;
  D = sqrt((m12 * m12 + m13 * m13) + m14 * m14);
  D1_tmp = D * D;
  D1 = sqrt(1.0 - D1_tmp);
  if (D == 0.0) {
    for (i = 0; i < 16; i++) {
      M_0[i] = M[i];
      MD[i] = 0.0;
    }
    MD[0] = 1.0;
    MD[5] = 1.0;
    MD[10] = 1.0;
    MD[15] = 1.0;
  } else {
    MD[0] = 1.0;
    for (i = 0; i < 3; i++) {
      MD_tmp = (i + 1) << 2;
      d = dvec[i];
      MD[MD_tmp] = d;
      MD[i + 1] = d;
      MD[MD_tmp + 1] =
          D1 * (double)b[3 * i] + (1.0 - D1) * dvec[0] * dvec[i] / D1_tmp;
      MD[MD_tmp + 2] =
          D1 * (double)b[3 * i + 1] + (1.0 - D1) * dvec[1] * dvec[i] / D1_tmp;
      MD[MD_tmp + 3] =
          D1 * (double)b[3 * i + 2] + (1.0 - D1) * dvec[2] * dvec[i] / D1_tmp;
    }
    memcpy(&M_0[0], &M[0], 16U * sizeof(double));
    memcpy(&Mdelta[0], &MD[0], 16U * sizeof(double));
    xzgetrf(Mdelta, ipiv, &MD_tmp);
    for (j = 0; j < 4; j++) {
      MD_tmp = j << 2;
      for (k = 0; k < j; k++) {
        kBcol = k << 2;
        d = Mdelta[k + MD_tmp];
        if (d != 0.0) {
          M_0[MD_tmp] -= d * M_0[kBcol];
          M_0[MD_tmp + 1] -= d * M_0[kBcol + 1];
          M_0[MD_tmp + 2] -= d * M_0[kBcol + 2];
          M_0[MD_tmp + 3] -= d * M_0[kBcol + 3];
        }
      }
      D = 1.0 / Mdelta[j + MD_tmp];
      M_0[MD_tmp] *= D;
      M_0[MD_tmp + 1] *= D;
      M_0[MD_tmp + 2] *= D;
      M_0[MD_tmp + 3] *= D;
    }
    for (j = 3; j >= 0; j--) {
      MD_tmp = (j << 2) - 1;
      i = j + 2;
      for (k = i; k < 5; k++) {
        kBcol = (k - 1) << 2;
        d = Mdelta[k + MD_tmp];
        if (d != 0.0) {
          M_0[MD_tmp + 1] -= d * M_0[kBcol];
          M_0[MD_tmp + 2] -= d * M_0[kBcol + 1];
          M_0[MD_tmp + 3] -= d * M_0[kBcol + 2];
          M_0[MD_tmp + 4] -= d * M_0[kBcol + 3];
        }
      }
    }
    for (j = 2; j >= 0; j--) {
      i = ipiv[j];
      if (i != j + 1) {
        k = j << 2;
        D = M_0[k];
        MD_tmp = (i - 1) << 2;
        M_0[k] = M_0[MD_tmp];
        M_0[MD_tmp] = D;
        D = M_0[k + 1];
        M_0[k + 1] = M_0[MD_tmp + 1];
        M_0[MD_tmp + 1] = D;
        D = M_0[k + 2];
        M_0[k + 2] = M_0[MD_tmp + 2];
        M_0[MD_tmp + 2] = D;
        D = M_0[k + 3];
        M_0[k + 3] = M_0[MD_tmp + 3];
        M_0[MD_tmp + 3] = D;
      }
    }
  }
  /*  Phase shift Matrix */
  isodd = true;
  for (k = 0; k < 9; k++) {
    if (isodd) {
      D = M_0[(k % 3 + ((k / 3 + 1) << 2)) + 1];
      if (rtIsInf(D) || rtIsNaN(D)) {
        isodd = false;
      }
    } else {
      isodd = false;
    }
  }
  if (isodd) {
    for (i = 0; i < 3; i++) {
      MD_tmp = (i + 1) << 2;
      b_D1[3 * i] = M_0[MD_tmp + 1];
      b_D1[3 * i + 1] = M_0[MD_tmp + 2];
      b_D1[3 * i + 2] = M_0[MD_tmp + 3];
    }
    svd(b_D1, U, dvec, V);
  } else {
    for (i = 0; i < 9; i++) {
      U[i] = rtNaN;
      V[i] = rtNaN;
    }
  }
  xzgetrf(M, ipiv, &MD_tmp);
  isodd = (ipiv[0] > 1);
  if (ipiv[1] > 2) {
    isodd = !isodd;
  }
  D = M[0] * M[5] * M[10] * M[15];
  if (ipiv[2] > 3) {
    isodd = !isodd;
  }
  if (isodd) {
    D = -D;
  }
  if (D < 0.0) {
    dvec[2] = -1.0;
  } else {
    dvec[2] = 1.0;
  }
  for (i = 0; i < 9; i++) {
    b_b[i] = 0;
  }
  b_b[0] = 1;
  b_b[4] = 1;
  b_b[8] = (signed char)dvec[2];
  for (i = 0; i < 3; i++) {
    d = U[i];
    D = U[i + 3];
    D1_tmp = U[i + 6];
    for (MD_tmp = 0; MD_tmp < 3; MD_tmp++) {
      b_D1[i + 3 * MD_tmp] =
          (d * (double)b_b[3 * MD_tmp] + D * (double)b_b[3 * MD_tmp + 1]) +
          D1_tmp * (double)b_b[3 * MD_tmp + 2];
    }
    d = b_D1[i];
    D = b_D1[i + 3];
    D1_tmp = b_D1[i + 6];
    for (MD_tmp = 0; MD_tmp < 3; MD_tmp++) {
      U[i + 3 * MD_tmp] =
          (d * V[MD_tmp] + D * V[MD_tmp + 3]) + D1_tmp * V[MD_tmp + 6];
    }
  }
  M[0] = 1.0;
  M[4] = 0.0;
  M[8] = 0.0;
  M[12] = 0.0;
  for (i = 0; i < 3; i++) {
    M[i + 1] = 0.0;
    MD_tmp = (i + 1) << 2;
    M[MD_tmp + 1] = U[3 * i];
    M[MD_tmp + 2] = U[3 * i + 1];
    M[MD_tmp + 3] = U[3 * i + 2];
  }
  /*  Depolarisation Matrix */
  for (i = 0; i < 4; i++) {
    d = M_0[i];
    D = M_0[i + 4];
    D1_tmp = M_0[i + 8];
    D1 = M_0[i + 12];
    for (MD_tmp = 0; MD_tmp < 4; MD_tmp++) {
      Mdelta[i + (MD_tmp << 2)] =
          ((d * M[MD_tmp] + D * M[MD_tmp + 4]) + D1_tmp * M[MD_tmp + 8]) +
          D1 * M[MD_tmp + 12];
    }
  }
  *t11 = MD[0];
  *t12 = MD[4];
  *t13 = MD[8];
  *t14 = MD[12];
  *t21 = MD[1];
  *t22 = MD[5];
  *t23 = MD[9];
  *t24 = MD[13];
  *t31 = MD[2];
  *t32 = MD[6];
  *t33 = MD[10];
  *t34 = MD[14];
  *t41 = MD[3];
  *t42 = MD[7];
  *t43 = MD[11];
  *t44 = MD[15];
  *p11 = M[0];
  *p12 = M[4];
  *p13 = M[8];
  *p14 = M[12];
  *p21 = M[1];
  *p22 = M[5];
  *p23 = M[9];
  *p24 = M[13];
  *p31 = M[2];
  *p32 = M[6];
  *p33 = M[10];
  *p34 = M[14];
  *p41 = M[3];
  *p42 = M[7];
  *p43 = M[11];
  *p44 = M[15];
  *d11 = Mdelta[0];
  *d12 = Mdelta[4];
  *d13 = Mdelta[8];
  *d14 = Mdelta[12];
  *d21 = Mdelta[1];
  *d22 = Mdelta[5];
  *d23 = Mdelta[9];
  *d24 = Mdelta[13];
  *d31 = Mdelta[2];
  *d32 = Mdelta[6];
  *d33 = Mdelta[10];
  *d34 = Mdelta[14];
  *d41 = Mdelta[3];
  *d42 = Mdelta[7];
  *d43 = Mdelta[11];
  *d44 = Mdelta[15];
}

/*
 * File trailer for compute_MM_polarLuChipman.c
 *
 * [EOF]
 */
