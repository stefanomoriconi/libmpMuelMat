/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: eig.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 19-Jul-2022 14:47:38
 */

/* Include Files */
#include "eig.h"
//#include "eig4x4cmplx_data.h"
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
 * Arguments    : const creal_T A[16]
 *                creal_T V[16]
 *                creal_T D[16]
 * Return Type  : void
 */
void eig(const creal_T A[16], creal_T V[16], creal_T D[16])
{
  creal_T At[16];
  creal_T beta1[4];
  creal_T work[4];
  creal_T tau[3];
  creal_T c;
  double absxk;
  double alpha1_im;
  double colnorm;
  double im;
  double scale;
  double t;
  int alpha1_re_tmp_tmp;
  int b_i;
  int c_i;
  int exitg1;
  int i;
  int i1;
  int ia;
  int im1n_tmp_tmp;
  int in;
  int j;
  int jA;
  int knt;
  int lastc;
  int lastv;
  boolean_T exitg2;
  boolean_T p;
  p = true;
  for (jA = 0; jA < 16; jA++) {
    if ((!p) || (rtIsInf(A[jA].re) || rtIsInf(A[jA].im) ||
                 (rtIsNaN(A[jA].re) || rtIsNaN(A[jA].im)))) {
      p = false;
    }
  }
  if (!p) {
    for (i = 0; i < 16; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
      D[i].re = 0.0;
      D[i].im = 0.0;
    }
    D[0].re = rtNaN;
    D[0].im = 0.0;
    D[5].re = rtNaN;
    D[5].im = 0.0;
    D[10].re = rtNaN;
    D[10].im = 0.0;
    D[15].re = rtNaN;
    D[15].im = 0.0;
  } else {
    p = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 4)) {
      b_i = 0;
      do {
        exitg1 = 0;
        if (b_i <= j) {
          knt = j + (b_i << 2);
          c_i = b_i + (j << 2);
          if ((!(A[c_i].re == A[knt].re)) || (!(A[c_i].im == -A[knt].im))) {
            p = false;
            exitg1 = 1;
          } else {
            b_i++;
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
      for (jA = 0; jA < 16; jA++) {
        if ((!p) || (rtIsInf(A[jA].re) || rtIsInf(A[jA].im) ||
                     (rtIsNaN(A[jA].re) || rtIsNaN(A[jA].im)))) {
          p = false;
        }
      }
      if (!p) {
        for (i = 0; i < 16; i++) {
          V[i].re = rtNaN;
          V[i].im = 0.0;
        }
        knt = 2;
        for (j = 0; j < 3; j++) {
          if (knt <= 4) {
            memset(&V[(j * 4 + knt) + -1], 0, (5 - knt) * sizeof(creal_T));
          }
          knt++;
        }
        for (i = 0; i < 16; i++) {
          D[i].re = rtNaN;
          D[i].im = 0.0;
        }
      } else {
        memcpy(&D[0], &A[0], 16U * sizeof(creal_T));
        memset(&work[0], 0, 4U * sizeof(creal_T));
        for (b_i = 0; b_i < 3; b_i++) {
          im1n_tmp_tmp = b_i << 2;
          in = (b_i + 1) << 2;
          alpha1_re_tmp_tmp = (b_i + im1n_tmp_tmp) + 1;
          colnorm = D[alpha1_re_tmp_tmp].re;
          alpha1_im = D[alpha1_re_tmp_tmp].im;
          if (b_i + 3 < 4) {
            c_i = b_i + 1;
          } else {
            c_i = 2;
          }
          c_i = (c_i + im1n_tmp_tmp) + 2;
          tau[b_i].re = 0.0;
          tau[b_i].im = 0.0;
          scale = xnrm2(2 - b_i, D, c_i);
          if ((scale != 0.0) || (D[alpha1_re_tmp_tmp].im != 0.0)) {
            t = xdlapy3(colnorm, alpha1_im, scale);
            if (colnorm >= 0.0) {
              t = -t;
            }
            if (fabs(t) < 1.0020841800044864E-292) {
              knt = -1;
              i = (c_i - b_i) + 1;
              do {
                knt++;
                for (jA = c_i; jA <= i; jA++) {
                  scale = D[jA - 1].im;
                  absxk = D[jA - 1].re;
                  im = 9.9792015476736E+291 * scale + 0.0 * absxk;
                  absxk = 9.9792015476736E+291 * absxk - 0.0 * scale;
                  D[jA - 1].re = absxk;
                  D[jA - 1].im = im;
                }
                t *= 9.9792015476736E+291;
                colnorm *= 9.9792015476736E+291;
                alpha1_im *= 9.9792015476736E+291;
              } while (!(fabs(t) >= 1.0020841800044864E-292));
              t = xdlapy3(colnorm, alpha1_im, xnrm2(2 - b_i, D, c_i));
              if (colnorm >= 0.0) {
                t = -t;
              }
              scale = t - colnorm;
              if (0.0 - alpha1_im == 0.0) {
                tau[b_i].re = scale / t;
                tau[b_i].im = 0.0;
              } else if (scale == 0.0) {
                tau[b_i].re = 0.0;
                tau[b_i].im = (0.0 - alpha1_im) / t;
              } else {
                tau[b_i].re = scale / t;
                tau[b_i].im = (0.0 - alpha1_im) / t;
              }
              c.re = colnorm - t;
              c.im = alpha1_im;
              c = recip(c);
              for (jA = c_i; jA <= i; jA++) {
                scale = D[jA - 1].im;
                absxk = D[jA - 1].re;
                im = c.re * scale + c.im * absxk;
                absxk = c.re * absxk - c.im * scale;
                D[jA - 1].re = absxk;
                D[jA - 1].im = im;
              }
              for (jA = 0; jA <= knt; jA++) {
                t *= 1.0020841800044864E-292;
              }
              colnorm = t;
              alpha1_im = 0.0;
            } else {
              scale = t - colnorm;
              if (0.0 - alpha1_im == 0.0) {
                tau[b_i].re = scale / t;
                tau[b_i].im = 0.0;
              } else if (scale == 0.0) {
                tau[b_i].re = 0.0;
                tau[b_i].im = (0.0 - alpha1_im) / t;
              } else {
                tau[b_i].re = scale / t;
                tau[b_i].im = (0.0 - alpha1_im) / t;
              }
              c.re = colnorm - t;
              c.im = alpha1_im;
              c = recip(c);
              i = (c_i - b_i) + 1;
              for (jA = c_i; jA <= i; jA++) {
                scale = D[jA - 1].im;
                absxk = D[jA - 1].re;
                im = c.re * scale + c.im * absxk;
                absxk = c.re * absxk - c.im * scale;
                D[jA - 1].re = absxk;
                D[jA - 1].im = im;
              }
              colnorm = t;
              alpha1_im = 0.0;
            }
          }
          D[alpha1_re_tmp_tmp].re = 1.0;
          D[alpha1_re_tmp_tmp].im = 0.0;
          jA = in + 1;
          if ((tau[b_i].re != 0.0) || (tau[b_i].im != 0.0)) {
            lastv = 2 - b_i;
            c_i = (alpha1_re_tmp_tmp - b_i) + 2;
            while ((lastv + 1 > 0) &&
                   ((D[c_i].re == 0.0) && (D[c_i].im == 0.0))) {
              lastv--;
              c_i--;
            }
            lastc = 4;
            exitg2 = false;
            while ((!exitg2) && (lastc > 0)) {
              c_i = in + lastc;
              ia = c_i;
              do {
                exitg1 = 0;
                if (ia <= c_i + (lastv << 2)) {
                  if ((D[ia - 1].re != 0.0) || (D[ia - 1].im != 0.0)) {
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
              i = (in + (lastv << 2)) + 1;
              for (knt = jA; knt <= i; knt += 4) {
                c_i = alpha1_re_tmp_tmp + (((knt - in) - 1) >> 2);
                c.re = D[c_i].re - 0.0 * D[c_i].im;
                c.im = D[c_i].im + 0.0 * D[c_i].re;
                i1 = (knt + lastc) - 1;
                for (ia = knt; ia <= i1; ia++) {
                  c_i = ia - knt;
                  scale = D[ia - 1].re;
                  absxk = D[ia - 1].im;
                  work[c_i].re += scale * c.re - absxk * c.im;
                  work[c_i].im += scale * c.im + absxk * c.re;
                }
              }
            }
            c.re = -tau[b_i].re;
            c.im = -tau[b_i].im;
            if ((!(c.re == 0.0)) || (!(c.im == 0.0))) {
              jA = in;
              for (j = 0; j <= lastv; j++) {
                c_i = alpha1_re_tmp_tmp + j;
                if ((D[c_i].re != 0.0) || (D[c_i].im != 0.0)) {
                  scale = D[c_i].re * c.re + D[c_i].im * c.im;
                  absxk = D[c_i].re * c.im - D[c_i].im * c.re;
                  i = jA + 1;
                  i1 = lastc + jA;
                  for (c_i = i; c_i <= i1; c_i++) {
                    knt = (c_i - jA) - 1;
                    D[c_i - 1].re +=
                        work[knt].re * scale - work[knt].im * absxk;
                    D[c_i - 1].im +=
                        work[knt].re * absxk + work[knt].im * scale;
                  }
                }
                jA += 4;
              }
            }
          }
          c.re = tau[b_i].re;
          c.im = -tau[b_i].im;
          xzlarf(3 - b_i, 3 - b_i, (b_i + im1n_tmp_tmp) + 2, c, D,
                 (b_i + in) + 2, work);
          D[alpha1_re_tmp_tmp].re = colnorm;
          D[alpha1_re_tmp_tmp].im = alpha1_im;
        }
        memcpy(&V[0], &D[0], 16U * sizeof(creal_T));
        for (j = 2; j >= 0; j--) {
          ia = (j + 1) << 2;
          for (b_i = 0; b_i <= j; b_i++) {
            i = ia + b_i;
            V[i].re = 0.0;
            V[i].im = 0.0;
          }
          i = j + 3;
          for (b_i = i; b_i < 5; b_i++) {
            knt = ia + b_i;
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
        for (b_i = 2; b_i >= 0; b_i--) {
          knt = (b_i + (b_i << 2)) + 5;
          if (b_i + 1 < 3) {
            V[knt].re = 1.0;
            V[knt].im = 0.0;
            xzlarf(3 - b_i, 2 - b_i, knt + 1, tau[b_i], V, knt + 5, work);
            c_i = knt + 2;
            c.re = -tau[b_i].re;
            c.im = -tau[b_i].im;
            i = (knt - b_i) + 3;
            for (jA = c_i; jA <= i; jA++) {
              scale = V[jA - 1].im;
              absxk = V[jA - 1].re;
              im = c.re * scale + c.im * absxk;
              absxk = c.re * absxk - c.im * scale;
              V[jA - 1].re = absxk;
              V[jA - 1].im = im;
            }
          }
          V[knt].re = 1.0 - tau[b_i].re;
          V[knt].im = 0.0 - tau[b_i].im;
          for (j = 0; j < b_i; j++) {
            i = (knt - j) - 1;
            V[i].re = 0.0;
            V[i].im = 0.0;
          }
        }
        xhseqr(D, V);
      }
      D[0].im = 0.0;
      for (j = 0; j < 3; j++) {
        i = (j + 1) << 2;
        D[(j + i) + 1].im = 0.0;
        i1 = (j + (j << 2)) + 1;
        D[i1].re = 0.0;
        D[i1].im = 0.0;
        for (b_i = 0; b_i <= j; b_i++) {
          i1 = b_i + i;
          D[i1].re = 0.0;
          D[i1].im = 0.0;
        }
      }
    } else {
      memcpy(&At[0], &A[0], 16U * sizeof(creal_T));
      xzggev(At, &knt, work, beta1, V);
      for (knt = 0; knt <= 12; knt += 4) {
        colnorm = 0.0;
        scale = 3.3121686421112381E-170;
        c_i = knt + 4;
        for (jA = knt + 1; jA <= c_i; jA++) {
          absxk = fabs(V[jA - 1].re);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = colnorm * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }
          absxk = fabs(V[jA - 1].im);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = colnorm * t * t + 1.0;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }
        }
        colnorm = scale * sqrt(colnorm);
        for (j = knt + 1; j <= c_i; j++) {
          scale = V[j - 1].re;
          absxk = V[j - 1].im;
          if (absxk == 0.0) {
            scale /= colnorm;
            im = 0.0;
          } else if (scale == 0.0) {
            scale = 0.0;
            im = absxk / colnorm;
          } else {
            scale /= colnorm;
            im = absxk / colnorm;
          }
          V[j - 1].re = scale;
          V[j - 1].im = im;
        }
      }
      memset(&D[0], 0, 16U * sizeof(creal_T));
      if (beta1[0].im == 0.0) {
        if (work[0].im == 0.0) {
          D[0].re = work[0].re / beta1[0].re;
          D[0].im = 0.0;
        } else if (work[0].re == 0.0) {
          D[0].re = 0.0;
          D[0].im = work[0].im / beta1[0].re;
        } else {
          D[0].re = work[0].re / beta1[0].re;
          D[0].im = work[0].im / beta1[0].re;
        }
      } else if (beta1[0].re == 0.0) {
        if (work[0].re == 0.0) {
          D[0].re = work[0].im / beta1[0].im;
          D[0].im = 0.0;
        } else if (work[0].im == 0.0) {
          D[0].re = 0.0;
          D[0].im = -(work[0].re / beta1[0].im);
        } else {
          D[0].re = work[0].im / beta1[0].im;
          D[0].im = -(work[0].re / beta1[0].im);
        }
      } else {
        t = fabs(beta1[0].re);
        scale = fabs(beta1[0].im);
        if (t > scale) {
          scale = beta1[0].im / beta1[0].re;
          absxk = beta1[0].re + scale * beta1[0].im;
          D[0].re = (work[0].re + scale * work[0].im) / absxk;
          D[0].im = (work[0].im - scale * work[0].re) / absxk;
        } else if (scale == t) {
          if (beta1[0].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          if (beta1[0].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }
          D[0].re = (work[0].re * scale + work[0].im * absxk) / t;
          D[0].im = (work[0].im * scale - work[0].re * absxk) / t;
        } else {
          scale = beta1[0].re / beta1[0].im;
          absxk = beta1[0].im + scale * beta1[0].re;
          D[0].re = (scale * work[0].re + work[0].im) / absxk;
          D[0].im = (scale * work[0].im - work[0].re) / absxk;
        }
      }
      if (beta1[1].im == 0.0) {
        if (work[1].im == 0.0) {
          D[5].re = work[1].re / beta1[1].re;
          D[5].im = 0.0;
        } else if (work[1].re == 0.0) {
          D[5].re = 0.0;
          D[5].im = work[1].im / beta1[1].re;
        } else {
          D[5].re = work[1].re / beta1[1].re;
          D[5].im = work[1].im / beta1[1].re;
        }
      } else if (beta1[1].re == 0.0) {
        if (work[1].re == 0.0) {
          D[5].re = work[1].im / beta1[1].im;
          D[5].im = 0.0;
        } else if (work[1].im == 0.0) {
          D[5].re = 0.0;
          D[5].im = -(work[1].re / beta1[1].im);
        } else {
          D[5].re = work[1].im / beta1[1].im;
          D[5].im = -(work[1].re / beta1[1].im);
        }
      } else {
        t = fabs(beta1[1].re);
        scale = fabs(beta1[1].im);
        if (t > scale) {
          scale = beta1[1].im / beta1[1].re;
          absxk = beta1[1].re + scale * beta1[1].im;
          D[5].re = (work[1].re + scale * work[1].im) / absxk;
          D[5].im = (work[1].im - scale * work[1].re) / absxk;
        } else if (scale == t) {
          if (beta1[1].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          if (beta1[1].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }
          D[5].re = (work[1].re * scale + work[1].im * absxk) / t;
          D[5].im = (work[1].im * scale - work[1].re * absxk) / t;
        } else {
          scale = beta1[1].re / beta1[1].im;
          absxk = beta1[1].im + scale * beta1[1].re;
          D[5].re = (scale * work[1].re + work[1].im) / absxk;
          D[5].im = (scale * work[1].im - work[1].re) / absxk;
        }
      }
      if (beta1[2].im == 0.0) {
        if (work[2].im == 0.0) {
          D[10].re = work[2].re / beta1[2].re;
          D[10].im = 0.0;
        } else if (work[2].re == 0.0) {
          D[10].re = 0.0;
          D[10].im = work[2].im / beta1[2].re;
        } else {
          D[10].re = work[2].re / beta1[2].re;
          D[10].im = work[2].im / beta1[2].re;
        }
      } else if (beta1[2].re == 0.0) {
        if (work[2].re == 0.0) {
          D[10].re = work[2].im / beta1[2].im;
          D[10].im = 0.0;
        } else if (work[2].im == 0.0) {
          D[10].re = 0.0;
          D[10].im = -(work[2].re / beta1[2].im);
        } else {
          D[10].re = work[2].im / beta1[2].im;
          D[10].im = -(work[2].re / beta1[2].im);
        }
      } else {
        t = fabs(beta1[2].re);
        scale = fabs(beta1[2].im);
        if (t > scale) {
          scale = beta1[2].im / beta1[2].re;
          absxk = beta1[2].re + scale * beta1[2].im;
          D[10].re = (work[2].re + scale * work[2].im) / absxk;
          D[10].im = (work[2].im - scale * work[2].re) / absxk;
        } else if (scale == t) {
          if (beta1[2].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          if (beta1[2].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }
          D[10].re = (work[2].re * scale + work[2].im * absxk) / t;
          D[10].im = (work[2].im * scale - work[2].re * absxk) / t;
        } else {
          scale = beta1[2].re / beta1[2].im;
          absxk = beta1[2].im + scale * beta1[2].re;
          D[10].re = (scale * work[2].re + work[2].im) / absxk;
          D[10].im = (scale * work[2].im - work[2].re) / absxk;
        }
      }
      if (beta1[3].im == 0.0) {
        if (work[3].im == 0.0) {
          D[15].re = work[3].re / beta1[3].re;
          D[15].im = 0.0;
        } else if (work[3].re == 0.0) {
          D[15].re = 0.0;
          D[15].im = work[3].im / beta1[3].re;
        } else {
          D[15].re = work[3].re / beta1[3].re;
          D[15].im = work[3].im / beta1[3].re;
        }
      } else if (beta1[3].re == 0.0) {
        if (work[3].re == 0.0) {
          D[15].re = work[3].im / beta1[3].im;
          D[15].im = 0.0;
        } else if (work[3].im == 0.0) {
          D[15].re = 0.0;
          D[15].im = -(work[3].re / beta1[3].im);
        } else {
          D[15].re = work[3].im / beta1[3].im;
          D[15].im = -(work[3].re / beta1[3].im);
        }
      } else {
        t = fabs(beta1[3].re);
        scale = fabs(beta1[3].im);
        if (t > scale) {
          scale = beta1[3].im / beta1[3].re;
          absxk = beta1[3].re + scale * beta1[3].im;
          D[15].re = (work[3].re + scale * work[3].im) / absxk;
          D[15].im = (work[3].im - scale * work[3].re) / absxk;
        } else if (scale == t) {
          if (beta1[3].re > 0.0) {
            scale = 0.5;
          } else {
            scale = -0.5;
          }
          if (beta1[3].im > 0.0) {
            absxk = 0.5;
          } else {
            absxk = -0.5;
          }
          D[15].re = (work[3].re * scale + work[3].im * absxk) / t;
          D[15].im = (work[3].im * scale - work[3].re * absxk) / t;
        } else {
          scale = beta1[3].re / beta1[3].im;
          absxk = beta1[3].im + scale * beta1[3].re;
          D[15].re = (scale * work[3].re + work[3].im) / absxk;
          D[15].im = (scale * work[3].im - work[3].re) / absxk;
        }
      }
    }
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
