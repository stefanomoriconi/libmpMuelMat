/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzhgeqz.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 19-Jul-2022 14:47:38
 */

/* Include Files */
#include "xzhgeqz.h"
//#include "eig4x4cmplx_data.h"
#include "eigL4x4real_data.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzlartg.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : creal_T A[16]
 *                int ilo
 *                int ihi
 *                creal_T Z[16]
 *                int *info
 *                creal_T alpha1[4]
 *                creal_T beta1[4]
 * Return Type  : void
 */
void xzhgeqz(creal_T A[16], int ilo, int ihi, creal_T Z[16], int *info,
             creal_T alpha1[4], creal_T beta1[4])
{
  creal_T b_ascale;
  creal_T ctemp;
  creal_T shift;
  double ad22_im;
  double ad22_re;
  double anorm;
  double ascale;
  double b_atol;
  double colscale;
  double colssq;
  double eshift_im;
  double eshift_re;
  double scale;
  double ssq;
  double t;
  double t1_im;
  double t1_im_tmp;
  double t1_re;
  int col;
  int exitg1;
  int i;
  int ifirst;
  int iiter;
  int ilast;
  int ilastm1;
  int istart;
  int j;
  int jiter;
  int jm1;
  int nm1;
  int row;
  boolean_T b_guard1 = false;
  boolean_T exitg2;
  boolean_T failed;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  *info = 0;
  alpha1[0].re = 0.0;
  alpha1[0].im = 0.0;
  beta1[0].re = 1.0;
  beta1[0].im = 0.0;
  alpha1[1].re = 0.0;
  alpha1[1].im = 0.0;
  beta1[1].re = 1.0;
  beta1[1].im = 0.0;
  alpha1[2].re = 0.0;
  alpha1[2].im = 0.0;
  beta1[2].re = 1.0;
  beta1[2].im = 0.0;
  alpha1[3].re = 0.0;
  alpha1[3].im = 0.0;
  beta1[3].re = 1.0;
  beta1[3].im = 0.0;
  eshift_re = 0.0;
  eshift_im = 0.0;
  ctemp.re = 0.0;
  ctemp.im = 0.0;
  anorm = 0.0;
  if (ilo <= ihi) {
    scale = 3.3121686421112381E-170;
    ssq = 0.0;
    nm1 = ihi - ilo;
    for (j = 0; j <= nm1; j++) {
      colscale = 3.3121686421112381E-170;
      colssq = 0.0;
      col = (ilo + j) - 1;
      jm1 = j + 1;
      if (jm1 >= nm1) {
        jm1 = nm1;
      }
      i = ilo + jm1;
      for (row = ilo; row <= i; row++) {
        jm1 = (row + (col << 2)) - 1;
        anorm = fabs(A[jm1].re);
        if (anorm > colscale) {
          t = colscale / anorm;
          colssq = colssq * t * t + 1.0;
          colscale = anorm;
        } else {
          t = anorm / colscale;
          colssq += t * t;
        }
        anorm = fabs(A[jm1].im);
        if (anorm > colscale) {
          t = colscale / anorm;
          colssq = colssq * t * t + 1.0;
          colscale = anorm;
        } else {
          t = anorm / colscale;
          colssq += t * t;
        }
      }
      if (scale >= colscale) {
        t = colscale / scale;
        ssq += t * t * colssq;
      } else {
        t = scale / colscale;
        ssq = colssq + t * t * ssq;
        scale = colscale;
      }
    }
    anorm = scale * sqrt(ssq);
  }
  t = 2.2204460492503131E-16 * anorm;
  b_atol = 2.2250738585072014E-308;
  if (t > 2.2250738585072014E-308) {
    b_atol = t;
  }
  t = 2.2250738585072014E-308;
  if (anorm > 2.2250738585072014E-308) {
    t = anorm;
  }
  ascale = 1.0 / t;
  failed = true;
  i = ihi + 1;
  for (j = i; j < 5; j++) {
    alpha1[j - 1] = A[(j + ((j - 1) << 2)) - 1];
  }
  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 0;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
        b_guard1 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          b_guard1 = true;
        } else {
          i = ilast + (ilastm1 << 2);
          if (fabs(A[i].re) + fabs(A[i].im) <= b_atol) {
            A[i].re = 0.0;
            A[i].im = 0.0;
            goto60 = true;
            b_guard1 = true;
          } else {
            j = ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (j + 1 >= ilo)) {
              if (j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                i = j + ((j - 1) << 2);
                if (fabs(A[i].re) + fabs(A[i].im) <= b_atol) {
                  A[i].re = 0.0;
                  A[i].im = 0.0;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  j--;
                  guard3 = false;
                }
              }
            }
            if (guard3) {
              ifirst = j + 1;
              goto70 = true;
            }
            if (goto70) {
              b_guard1 = true;
            } else {
              alpha1[0].re = rtNaN;
              alpha1[0].im = 0.0;
              beta1[0].re = rtNaN;
              beta1[0].im = 0.0;
              alpha1[1].re = rtNaN;
              alpha1[1].im = 0.0;
              beta1[1].re = rtNaN;
              beta1[1].im = 0.0;
              alpha1[2].re = rtNaN;
              alpha1[2].im = 0.0;
              beta1[2].re = rtNaN;
              beta1[2].im = 0.0;
              alpha1[3].re = rtNaN;
              alpha1[3].im = 0.0;
              beta1[3].re = rtNaN;
              beta1[3].im = 0.0;
              for (i = 0; i < 16; i++) {
                Z[i].re = rtNaN;
                Z[i].im = 0.0;
              }
              *info = 1;
              exitg1 = 1;
            }
          }
        }
        if (b_guard1) {
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = A[ilast + (ilast << 2)];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              failed = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0;
              eshift_im = 0.0;
              jiter++;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              if (iiter - iiter / 10 * 10 != 0) {
                jm1 = ilastm1 + (ilastm1 << 2);
                anorm = ascale * A[jm1].re;
                t = ascale * A[jm1].im;
                if (t == 0.0) {
                  shift.re = anorm / 0.5;
                  shift.im = 0.0;
                } else if (anorm == 0.0) {
                  shift.re = 0.0;
                  shift.im = t / 0.5;
                } else {
                  shift.re = anorm / 0.5;
                  shift.im = t / 0.5;
                }
                jm1 = ilast + (ilast << 2);
                anorm = ascale * A[jm1].re;
                t = ascale * A[jm1].im;
                if (t == 0.0) {
                  ad22_re = anorm / 0.5;
                  ad22_im = 0.0;
                } else if (anorm == 0.0) {
                  ad22_re = 0.0;
                  ad22_im = t / 0.5;
                } else {
                  ad22_re = anorm / 0.5;
                  ad22_im = t / 0.5;
                }
                t1_re = 0.5 * (shift.re + ad22_re);
                t1_im = 0.5 * (shift.im + ad22_im);
                t1_im_tmp = t1_re * t1_im;
                jm1 = ilastm1 + (ilast << 2);
                anorm = ascale * A[jm1].re;
                t = ascale * A[jm1].im;
                if (t == 0.0) {
                  colscale = anorm / 0.5;
                  colssq = 0.0;
                } else if (anorm == 0.0) {
                  colscale = 0.0;
                  colssq = t / 0.5;
                } else {
                  colscale = anorm / 0.5;
                  colssq = t / 0.5;
                }
                jm1 = ilast + (ilastm1 << 2);
                anorm = ascale * A[jm1].re;
                t = ascale * A[jm1].im;
                if (t == 0.0) {
                  ssq = anorm / 0.5;
                  anorm = 0.0;
                } else if (anorm == 0.0) {
                  ssq = 0.0;
                  anorm = t / 0.5;
                } else {
                  ssq = anorm / 0.5;
                  anorm = t / 0.5;
                }
                t = shift.re * ad22_re - shift.im * ad22_im;
                scale = shift.re * ad22_im + shift.im * ad22_re;
                shift.re = ((t1_re * t1_re - t1_im * t1_im) +
                            (colscale * ssq - colssq * anorm)) -
                           t;
                shift.im = ((t1_im_tmp + t1_im_tmp) +
                            (colscale * anorm + colssq * ssq)) -
                           scale;
                b_sqrt(&shift);
                if ((t1_re - ad22_re) * shift.re +
                        (t1_im - ad22_im) * shift.im <=
                    0.0) {
                  shift.re += t1_re;
                  shift.im += t1_im;
                } else {
                  shift.re = t1_re - shift.re;
                  shift.im = t1_im - shift.im;
                }
              } else {
                jm1 = ilast + (ilastm1 << 2);
                anorm = ascale * A[jm1].re;
                t = ascale * A[jm1].im;
                if (t == 0.0) {
                  colscale = anorm / 0.5;
                  colssq = 0.0;
                } else if (anorm == 0.0) {
                  colscale = 0.0;
                  colssq = t / 0.5;
                } else {
                  colscale = anorm / 0.5;
                  colssq = t / 0.5;
                }
                eshift_re += colscale;
                eshift_im += colssq;
                shift.re = eshift_re;
                shift.im = eshift_im;
              }
              j = ilastm1;
              nm1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                col = j << 2;
                row = j + col;
                ctemp.re = ascale * A[row].re - shift.re * 0.5;
                ctemp.im = ascale * A[row].im - shift.im * 0.5;
                anorm = fabs(ctemp.re) + fabs(ctemp.im);
                jm1 = nm1 + col;
                t = ascale * (fabs(A[jm1].re) + fabs(A[jm1].im));
                scale = anorm;
                if (t > anorm) {
                  scale = t;
                }
                if ((scale < 1.0) && (scale != 0.0)) {
                  anorm /= scale;
                  t /= scale;
                }
                i = j + ((j - 1) << 2);
                if ((fabs(A[i].re) + fabs(A[i].im)) * t <= anorm * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  nm1 = j;
                  j--;
                }
              }
              if (!goto90) {
                istart = ifirst;
                row = (ifirst + ((ifirst - 1) << 2)) - 1;
                ctemp.re = ascale * A[row].re - shift.re * 0.5;
                ctemp.im = ascale * A[row].im - shift.im * 0.5;
              }
              goto90 = false;
              jm1 = istart + ((istart - 1) << 2);
              b_ascale.re = ascale * A[jm1].re;
              b_ascale.im = ascale * A[jm1].im;
              b_xzlartg(ctemp, b_ascale, &anorm, &shift);
              j = istart;
              jm1 = istart - 2;
              while (j < ilast + 1) {
                if (j > istart) {
                  nm1 = j + (jm1 << 2);
                  xzlartg(A[nm1 - 1], A[nm1], &anorm, &shift,
                          &A[(j + (jm1 << 2)) - 1]);
                  A[nm1].re = 0.0;
                  A[nm1].im = 0.0;
                }
                for (nm1 = j; nm1 < 5; nm1++) {
                  row = j + ((nm1 - 1) << 2);
                  ad22_re = anorm * A[row - 1].re +
                            (shift.re * A[row].re - shift.im * A[row].im);
                  ad22_im = anorm * A[row - 1].im +
                            (shift.re * A[row].im + shift.im * A[row].re);
                  t = A[row - 1].im;
                  scale = A[row - 1].re;
                  A[row].re = anorm * A[row].re - (shift.re * A[row - 1].re +
                                                   shift.im * A[row - 1].im);
                  A[row].im =
                      anorm * A[row].im - (shift.re * t - shift.im * scale);
                  A[row - 1].re = ad22_re;
                  A[row - 1].im = ad22_im;
                }
                shift.re = -shift.re;
                shift.im = -shift.im;
                nm1 = j;
                if (ilast + 1 < j + 2) {
                  nm1 = ilast - 1;
                }
                for (jm1 = 1; jm1 <= nm1 + 2; jm1++) {
                  row = (jm1 + ((j - 1) << 2)) - 1;
                  col = (jm1 + (j << 2)) - 1;
                  ad22_re = anorm * A[col].re +
                            (shift.re * A[row].re - shift.im * A[row].im);
                  ad22_im = anorm * A[col].im +
                            (shift.re * A[row].im + shift.im * A[row].re);
                  t = A[col].im;
                  scale = A[col].re;
                  A[row].re = anorm * A[row].re -
                              (shift.re * A[col].re + shift.im * A[col].im);
                  A[row].im =
                      anorm * A[row].im - (shift.re * t - shift.im * scale);
                  A[col].re = ad22_re;
                  A[col].im = ad22_im;
                }
                row = (j - 1) << 2;
                col = j << 2;
                ad22_re = anorm * Z[col].re +
                          (shift.re * Z[row].re - shift.im * Z[row].im);
                ad22_im = anorm * Z[col].im +
                          (shift.re * Z[row].im + shift.im * Z[row].re);
                t = Z[col].im;
                scale = Z[col].re;
                Z[row].re = anorm * Z[row].re -
                            (shift.re * Z[col].re + shift.im * Z[col].im);
                Z[row].im =
                    anorm * Z[row].im - (shift.re * t - shift.im * scale);
                Z[col].re = ad22_re;
                Z[col].im = ad22_im;
                ad22_re = anorm * Z[col + 1].re +
                          (shift.re * Z[row + 1].re - shift.im * Z[row + 1].im);
                ad22_im = anorm * Z[col + 1].im +
                          (shift.re * Z[row + 1].im + shift.im * Z[row + 1].re);
                t = Z[col + 1].im;
                scale = Z[col + 1].re;
                Z[row + 1].re =
                    anorm * Z[row + 1].re -
                    (shift.re * Z[col + 1].re + shift.im * Z[col + 1].im);
                Z[row + 1].im =
                    anorm * Z[row + 1].im - (shift.re * t - shift.im * scale);
                Z[col + 1].re = ad22_re;
                Z[col + 1].im = ad22_im;
                ad22_re = anorm * Z[col + 2].re +
                          (shift.re * Z[row + 2].re - shift.im * Z[row + 2].im);
                ad22_im = anorm * Z[col + 2].im +
                          (shift.re * Z[row + 2].im + shift.im * Z[row + 2].re);
                t = Z[col + 2].im;
                scale = Z[col + 2].re;
                Z[row + 2].re =
                    anorm * Z[row + 2].re -
                    (shift.re * Z[col + 2].re + shift.im * Z[col + 2].im);
                Z[row + 2].im =
                    anorm * Z[row + 2].im - (shift.re * t - shift.im * scale);
                Z[col + 2].re = ad22_re;
                Z[col + 2].im = ad22_im;
                ad22_re = anorm * Z[col + 3].re +
                          (shift.re * Z[row + 3].re - shift.im * Z[row + 3].im);
                ad22_im = anorm * Z[col + 3].im +
                          (shift.re * Z[row + 3].im + shift.im * Z[row + 3].re);
                t = Z[col + 3].im;
                scale = Z[col + 3].re;
                Z[row + 3].re =
                    anorm * Z[row + 3].re -
                    (shift.re * Z[col + 3].re + shift.im * Z[col + 3].im);
                Z[row + 3].im =
                    anorm * Z[row + 3].im - (shift.re * t - shift.im * scale);
                Z[col + 3].re = ad22_re;
                Z[col + 3].im = ad22_im;
                jm1 = j - 1;
                j++;
              }
            }
            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }
  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      for (jm1 = 0; jm1 <= ilast; jm1++) {
        alpha1[jm1].re = rtNaN;
        alpha1[jm1].im = 0.0;
        beta1[jm1].re = rtNaN;
        beta1[jm1].im = 0.0;
      }
      for (i = 0; i < 16; i++) {
        Z[i].re = rtNaN;
        Z[i].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }
  if (guard1) {
    for (j = 0; j <= ilo - 2; j++) {
      alpha1[j] = A[j + (j << 2)];
    }
  }
}

/*
 * File trailer for xzhgeqz.c
 *
 * [EOF]
 */
