/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eigL4x4real.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 26-Jul-2022 11:35:47
 */

/* Include Files */
#include "eigL4x4real.h"
#include "eigL4x4real_data.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "xdlapy3.h"
#include "xhseqr.h"
#include "xnrm2.h"
#include "xzggev.h"
#include "xzlarf.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * (Complex) Matrix definition [4x4]
 *
 * Arguments    : double A11_re
 *                double A11_im
 *                double A12_re
 *                double A12_im
 *                double A13_re
 *                double A13_im
 *                double A14_re
 *                double A14_im
 *                double A21_re
 *                double A21_im
 *                double A22_re
 *                double A22_im
 *                double A23_re
 *                double A23_im
 *                double A24_re
 *                double A24_im
 *                double A31_re
 *                double A31_im
 *                double A32_re
 *                double A32_im
 *                double A33_re
 *                double A33_im
 *                double A34_re
 *                double A34_im
 *                double A41_re
 *                double A41_im
 *                double A42_re
 *                double A42_im
 *                double A43_re
 *                double A43_im
 *                double A44_re
 *                double A44_im
 *                double *L1_re
 *                double *L2_re
 *                double *L3_re
 *                double *L4_re
 * Return Type  : void
 */
void eigL4x4real(double A11_re, double A11_im, double A12_re, double A12_im,
                 double A13_re, double A13_im, double A14_re, double A14_im,
                 double A21_re, double A21_im, double A22_re, double A22_im,
                 double A23_re, double A23_im, double A24_re, double A24_im,
                 double A31_re, double A31_im, double A32_re, double A32_im,
                 double A33_re, double A33_im, double A34_re, double A34_im,
                 double A41_re, double A41_im, double A42_re, double A42_im,
                 double A43_re, double A43_im, double A44_re, double A44_im,
                 double *L1_re, double *L2_re, double *L3_re, double *L4_re)
{
  creal_T A[16];
  creal_T V[16];
  creal_T beta1[4];
  creal_T work[4];
  creal_T tau[3];
  creal_T c;
  double alpha1_im;
  double alpha1_re;
  double b_beta1;
  double d;
  double temp_im;
  double temp_re;
  int alpha1_re_tmp_tmp;
  int b_i;
  int exitg1;
  int i;
  int i1;
  int ia;
  int im1n_tmp_tmp;
  int in;
  int j;
  int jA;
  int k;
  int knt;
  int lastc;
  int lastv;
  boolean_T exitg2;
  boolean_T p;
  A[0].re = A11_re;
  A[0].im = A11_im;
  A[4].re = A12_re;
  A[4].im = A12_im;
  A[8].re = A13_re;
  A[8].im = A13_im;
  A[12].re = A14_re;
  A[12].im = A14_im;
  A[1].re = A21_re;
  A[1].im = A21_im;
  A[5].re = A22_re;
  A[5].im = A22_im;
  A[9].re = A23_re;
  A[9].im = A23_im;
  A[13].re = A24_re;
  A[13].im = A24_im;
  A[2].re = A31_re;
  A[2].im = A31_im;
  A[6].re = A32_re;
  A[6].im = A32_im;
  A[10].re = A33_re;
  A[10].im = A33_im;
  A[14].re = A34_re;
  A[14].im = A34_im;
  A[3].re = A41_re;
  A[3].im = A41_im;
  A[7].re = A42_re;
  A[7].im = A42_im;
  A[11].re = A43_re;
  A[11].im = A43_im;
  A[15].re = A44_re;
  A[15].im = A44_im;
  /*  (Complex) Matrix Eigen-Decomposition */
  p = true;
  for (k = 0; k < 16; k++) {
    if ((!p) || (rtIsInf(A[k].re) || rtIsInf(A[k].im) ||
                 (rtIsNaN(A[k].re) || rtIsNaN(A[k].im)))) {
      p = false;
    }
  }
  if (!p) {
    A[0].re = rtNaN;
    A[5].re = rtNaN;
    A[10].re = rtNaN;
    A[15].re = rtNaN;
  } else {
    p = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 4)) {
      i = 0;
      do {
        exitg1 = 0;
        if (i <= j) {
          knt = j + (i << 2);
          k = i + (j << 2);
          if ((!(A[k].re == A[knt].re)) || (!(A[k].im == -A[knt].im))) {
            p = false;
            exitg1 = 1;
          } else {
            i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);
      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
    if (p) {
      p = true;
      for (k = 0; k < 16; k++) {
        if ((!p) || (rtIsInf(A[k].re) || rtIsInf(A[k].im) ||
                     (rtIsNaN(A[k].re) || rtIsNaN(A[k].im)))) {
          p = false;
        }
      }
      if (!p) {
        for (b_i = 0; b_i < 16; b_i++) {
          A[b_i].re = rtNaN;
          A[b_i].im = 0.0;
        }
      } else {
        memset(&work[0], 0, 4U * sizeof(creal_T));
        for (i = 0; i < 3; i++) {
          im1n_tmp_tmp = i << 2;
          in = (i + 1) << 2;
          alpha1_re_tmp_tmp = (i + im1n_tmp_tmp) + 1;
          alpha1_re = A[alpha1_re_tmp_tmp].re;
          alpha1_im = A[alpha1_re_tmp_tmp].im;
          if (i + 3 < 4) {
            jA = i + 1;
          } else {
            jA = 2;
          }
          jA = (jA + im1n_tmp_tmp) + 2;
          tau[i].re = 0.0;
          tau[i].im = 0.0;
          temp_re = xnrm2(2 - i, A, jA);
          if ((temp_re != 0.0) || (A[alpha1_re_tmp_tmp].im != 0.0)) {
            b_beta1 = xdlapy3(alpha1_re, alpha1_im, temp_re);
            if (alpha1_re >= 0.0) {
              b_beta1 = -b_beta1;
            }
            if (fabs(b_beta1) < 1.0020841800044864E-292) {
              knt = -1;
              b_i = (jA - i) + 1;
              do {
                knt++;
                for (k = jA; k <= b_i; k++) {
                  temp_im = A[k - 1].im;
                  d = A[k - 1].re;
                  temp_re = 9.9792015476736E+291 * temp_im + 0.0 * d;
                  d = 9.9792015476736E+291 * d - 0.0 * temp_im;
                  A[k - 1].re = d;
                  A[k - 1].im = temp_re;
                }
                b_beta1 *= 9.9792015476736E+291;
                alpha1_re *= 9.9792015476736E+291;
                alpha1_im *= 9.9792015476736E+291;
              } while (!(fabs(b_beta1) >= 1.0020841800044864E-292));
              b_beta1 = xdlapy3(alpha1_re, alpha1_im, xnrm2(2 - i, A, jA));
              if (alpha1_re >= 0.0) {
                b_beta1 = -b_beta1;
              }
              temp_re = b_beta1 - alpha1_re;
              if (0.0 - alpha1_im == 0.0) {
                tau[i].re = temp_re / b_beta1;
                tau[i].im = 0.0;
              } else if (temp_re == 0.0) {
                tau[i].re = 0.0;
                tau[i].im = (0.0 - alpha1_im) / b_beta1;
              } else {
                tau[i].re = temp_re / b_beta1;
                tau[i].im = (0.0 - alpha1_im) / b_beta1;
              }
              c.re = alpha1_re - b_beta1;
              c.im = alpha1_im;
              c = recip(c);
              for (k = jA; k <= b_i; k++) {
                temp_im = A[k - 1].im;
                d = A[k - 1].re;
                temp_re = c.re * temp_im + c.im * d;
                d = c.re * d - c.im * temp_im;
                A[k - 1].re = d;
                A[k - 1].im = temp_re;
              }
              for (k = 0; k <= knt; k++) {
                b_beta1 *= 1.0020841800044864E-292;
              }
              alpha1_re = b_beta1;
              alpha1_im = 0.0;
            } else {
              temp_re = b_beta1 - alpha1_re;
              if (0.0 - alpha1_im == 0.0) {
                tau[i].re = temp_re / b_beta1;
                tau[i].im = 0.0;
              } else if (temp_re == 0.0) {
                tau[i].re = 0.0;
                tau[i].im = (0.0 - alpha1_im) / b_beta1;
              } else {
                tau[i].re = temp_re / b_beta1;
                tau[i].im = (0.0 - alpha1_im) / b_beta1;
              }
              c.re = alpha1_re - b_beta1;
              c.im = alpha1_im;
              c = recip(c);
              b_i = (jA - i) + 1;
              for (k = jA; k <= b_i; k++) {
                temp_im = A[k - 1].im;
                d = A[k - 1].re;
                temp_re = c.re * temp_im + c.im * d;
                d = c.re * d - c.im * temp_im;
                A[k - 1].re = d;
                A[k - 1].im = temp_re;
              }
              alpha1_re = b_beta1;
              alpha1_im = 0.0;
            }
          }
          A[alpha1_re_tmp_tmp].re = 1.0;
          A[alpha1_re_tmp_tmp].im = 0.0;
          jA = in + 1;
          if ((tau[i].re != 0.0) || (tau[i].im != 0.0)) {
            lastv = 2 - i;
            knt = (alpha1_re_tmp_tmp - i) + 2;
            while ((lastv + 1 > 0) &&
                   ((A[knt].re == 0.0) && (A[knt].im == 0.0))) {
              lastv--;
              knt--;
            }
            lastc = 4;
            exitg2 = false;
            while ((!exitg2) && (lastc > 0)) {
              knt = in + lastc;
              ia = knt;
              do {
                exitg1 = 0;
                if (ia <= knt + (lastv << 2)) {
                  if ((A[ia - 1].re != 0.0) || (A[ia - 1].im != 0.0)) {
                    exitg1 = 1;
                  } else {
                    ia += 4;
                  }
                } else {
                  lastc--;
                  exitg1 = 2;
                }
              } while (exitg1 == 0);
              if (exitg1 == 1) {
                exitg2 = true;
              }
            }
          } else {
            lastv = -1;
            lastc = 0;
          }
          if (lastv + 1 > 0) {
            if (lastc != 0) {
              if (0 <= lastc - 1) {
                memset(&work[0], 0, lastc * sizeof(creal_T));
              }
              b_i = (in + (lastv << 2)) + 1;
              for (k = jA; k <= b_i; k += 4) {
                knt = alpha1_re_tmp_tmp + (((k - in) - 1) >> 2);
                c.re = A[knt].re - 0.0 * A[knt].im;
                c.im = A[knt].im + 0.0 * A[knt].re;
                i1 = (k + lastc) - 1;
                for (ia = k; ia <= i1; ia++) {
                  knt = ia - k;
                  temp_im = A[ia - 1].re;
                  d = A[ia - 1].im;
                  work[knt].re += temp_im * c.re - d * c.im;
                  work[knt].im += temp_im * c.im + d * c.re;
                }
              }
            }
            c.re = -tau[i].re;
            c.im = -tau[i].im;
            if ((!(c.re == 0.0)) || (!(c.im == 0.0))) {
              jA = in;
              for (j = 0; j <= lastv; j++) {
                k = alpha1_re_tmp_tmp + j;
                if ((A[k].re != 0.0) || (A[k].im != 0.0)) {
                  temp_re = A[k].re * c.re + A[k].im * c.im;
                  temp_im = A[k].re * c.im - A[k].im * c.re;
                  b_i = jA + 1;
                  i1 = lastc + jA;
                  for (knt = b_i; knt <= i1; knt++) {
                    k = (knt - jA) - 1;
                    A[knt - 1].re +=
                        work[k].re * temp_re - work[k].im * temp_im;
                    A[knt - 1].im +=
                        work[k].re * temp_im + work[k].im * temp_re;
                  }
                }
                jA += 4;
              }
            }
          }
          c.re = tau[i].re;
          c.im = -tau[i].im;
          xzlarf(3 - i, 3 - i, (i + im1n_tmp_tmp) + 2, c, A, (i + in) + 2,
                 work);
          A[alpha1_re_tmp_tmp].re = alpha1_re;
          A[alpha1_re_tmp_tmp].im = alpha1_im;
        }
        memcpy(&V[0], &A[0], 16U * sizeof(creal_T));
        for (j = 2; j >= 0; j--) {
          ia = (j + 1) << 2;
          for (i = 0; i <= j; i++) {
            b_i = ia + i;
            V[b_i].re = 0.0;
            V[b_i].im = 0.0;
          }
          b_i = j + 3;
          for (i = b_i; i < 5; i++) {
            knt = ia + i;
            V[knt - 1] = V[knt - 5];
          }
        }
        V[1].re = 0.0;
        V[1].im = 0.0;
        V[2].re = 0.0;
        V[2].im = 0.0;
        V[3].re = 0.0;
        V[3].im = 0.0;
        V[0].re = 1.0;
        V[0].im = 0.0;
        memset(&work[0], 0, 4U * sizeof(creal_T));
        for (i = 2; i >= 0; i--) {
          knt = (i + (i << 2)) + 5;
          if (i + 1 < 3) {
            V[knt].re = 1.0;
            V[knt].im = 0.0;
            xzlarf(3 - i, 2 - i, knt + 1, tau[i], V, knt + 5, work);
            jA = knt + 2;
            c.re = -tau[i].re;
            c.im = -tau[i].im;
            b_i = (knt - i) + 3;
            for (k = jA; k <= b_i; k++) {
              temp_im = V[k - 1].im;
              d = V[k - 1].re;
              temp_re = c.re * temp_im + c.im * d;
              d = c.re * d - c.im * temp_im;
              V[k - 1].re = d;
              V[k - 1].im = temp_re;
            }
          }
          V[knt].re = 1.0 - tau[i].re;
          V[knt].im = 0.0 - tau[i].im;
          for (j = 0; j < i; j++) {
            b_i = (knt - j) - 1;
            V[b_i].re = 0.0;
            V[b_i].im = 0.0;
          }
        }
        xhseqr(A, V);
      }
      for (j = 0; j < 3; j++) {
        b_i = (j + 1) << 2;
        A[(j + b_i) + 1].im = 0.0;
        i1 = (j + (j << 2)) + 1;
        A[i1].re = 0.0;
        A[i1].im = 0.0;
        for (i = 0; i <= j; i++) {
          i1 = i + b_i;
          A[i1].re = 0.0;
          A[i1].im = 0.0;
        }
      }
    } else {
      xzggev(A, &knt, work, beta1, V);
      if (beta1[0].im == 0.0) {
        if (work[0].im == 0.0) {
          A[0].re = work[0].re / beta1[0].re;
        } else if (work[0].re == 0.0) {
          A[0].re = 0.0;
        } else {
          A[0].re = work[0].re / beta1[0].re;
        }
      } else if (beta1[0].re == 0.0) {
        if (work[0].re == 0.0) {
          A[0].re = work[0].im / beta1[0].im;
        } else if (work[0].im == 0.0) {
          A[0].re = 0.0;
        } else {
          A[0].re = work[0].im / beta1[0].im;
        }
      } else {
        temp_re = fabs(beta1[0].re);
        temp_im = fabs(beta1[0].im);
        if (temp_re > temp_im) {
          temp_re = beta1[0].im / beta1[0].re;
          A[0].re = (work[0].re + temp_re * work[0].im) /
                    (beta1[0].re + temp_re * beta1[0].im);
        } else if (temp_im == temp_re) {
          if (beta1[0].re > 0.0) {
            b_beta1 = 0.5;
          } else {
            b_beta1 = -0.5;
          }
          if (beta1[0].im > 0.0) {
            temp_im = 0.5;
          } else {
            temp_im = -0.5;
          }
          A[0].re = (work[0].re * b_beta1 + work[0].im * temp_im) / temp_re;
        } else {
          temp_re = beta1[0].re / beta1[0].im;
          A[0].re = (temp_re * work[0].re + work[0].im) /
                    (beta1[0].im + temp_re * beta1[0].re);
        }
      }
      if (beta1[1].im == 0.0) {
        if (work[1].im == 0.0) {
          A[5].re = work[1].re / beta1[1].re;
        } else if (work[1].re == 0.0) {
          A[5].re = 0.0;
        } else {
          A[5].re = work[1].re / beta1[1].re;
        }
      } else if (beta1[1].re == 0.0) {
        if (work[1].re == 0.0) {
          A[5].re = work[1].im / beta1[1].im;
        } else if (work[1].im == 0.0) {
          A[5].re = 0.0;
        } else {
          A[5].re = work[1].im / beta1[1].im;
        }
      } else {
        temp_re = fabs(beta1[1].re);
        temp_im = fabs(beta1[1].im);
        if (temp_re > temp_im) {
          temp_re = beta1[1].im / beta1[1].re;
          A[5].re = (work[1].re + temp_re * work[1].im) /
                    (beta1[1].re + temp_re * beta1[1].im);
        } else if (temp_im == temp_re) {
          if (beta1[1].re > 0.0) {
            b_beta1 = 0.5;
          } else {
            b_beta1 = -0.5;
          }
          if (beta1[1].im > 0.0) {
            temp_im = 0.5;
          } else {
            temp_im = -0.5;
          }
          A[5].re = (work[1].re * b_beta1 + work[1].im * temp_im) / temp_re;
        } else {
          temp_re = beta1[1].re / beta1[1].im;
          A[5].re = (temp_re * work[1].re + work[1].im) /
                    (beta1[1].im + temp_re * beta1[1].re);
        }
      }
      if (beta1[2].im == 0.0) {
        if (work[2].im == 0.0) {
          A[10].re = work[2].re / beta1[2].re;
        } else if (work[2].re == 0.0) {
          A[10].re = 0.0;
        } else {
          A[10].re = work[2].re / beta1[2].re;
        }
      } else if (beta1[2].re == 0.0) {
        if (work[2].re == 0.0) {
          A[10].re = work[2].im / beta1[2].im;
        } else if (work[2].im == 0.0) {
          A[10].re = 0.0;
        } else {
          A[10].re = work[2].im / beta1[2].im;
        }
      } else {
        temp_re = fabs(beta1[2].re);
        temp_im = fabs(beta1[2].im);
        if (temp_re > temp_im) {
          temp_re = beta1[2].im / beta1[2].re;
          A[10].re = (work[2].re + temp_re * work[2].im) /
                     (beta1[2].re + temp_re * beta1[2].im);
        } else if (temp_im == temp_re) {
          if (beta1[2].re > 0.0) {
            b_beta1 = 0.5;
          } else {
            b_beta1 = -0.5;
          }
          if (beta1[2].im > 0.0) {
            temp_im = 0.5;
          } else {
            temp_im = -0.5;
          }
          A[10].re = (work[2].re * b_beta1 + work[2].im * temp_im) / temp_re;
        } else {
          temp_re = beta1[2].re / beta1[2].im;
          A[10].re = (temp_re * work[2].re + work[2].im) /
                     (beta1[2].im + temp_re * beta1[2].re);
        }
      }
      if (beta1[3].im == 0.0) {
        if (work[3].im == 0.0) {
          A[15].re = work[3].re / beta1[3].re;
        } else if (work[3].re == 0.0) {
          A[15].re = 0.0;
        } else {
          A[15].re = work[3].re / beta1[3].re;
        }
      } else if (beta1[3].re == 0.0) {
        if (work[3].re == 0.0) {
          A[15].re = work[3].im / beta1[3].im;
        } else if (work[3].im == 0.0) {
          A[15].re = 0.0;
        } else {
          A[15].re = work[3].im / beta1[3].im;
        }
      } else {
        temp_re = fabs(beta1[3].re);
        temp_im = fabs(beta1[3].im);
        if (temp_re > temp_im) {
          temp_re = beta1[3].im / beta1[3].re;
          A[15].re = (work[3].re + temp_re * work[3].im) /
                     (beta1[3].re + temp_re * beta1[3].im);
        } else if (temp_im == temp_re) {
          if (beta1[3].re > 0.0) {
            b_beta1 = 0.5;
          } else {
            b_beta1 = -0.5;
          }
          if (beta1[3].im > 0.0) {
            temp_im = 0.5;
          } else {
            temp_im = -0.5;
          }
          A[15].re = (work[3].re * b_beta1 + work[3].im * temp_im) / temp_re;
        } else {
          temp_re = beta1[3].re / beta1[3].im;
          A[15].re = (temp_re * work[3].re + work[3].im) /
                     (beta1[3].im + temp_re * beta1[3].re);
        }
      }
    }
  }
  /*  Diagonal Eigenvalue Matrix Values */
  *L1_re = A[0].re;
  *L2_re = A[5].re;
  *L3_re = A[10].re;
  *L4_re = A[15].re;
}

/*
 * File trailer for eigL4x4real.c
 *
 * [EOF]
 */
