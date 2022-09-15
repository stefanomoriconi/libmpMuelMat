/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzggev.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 19-Jul-2022 14:47:38
 */

/* Include Files */
#include "xzggev.h"
//#include "eig4x4cmplx_rtwutil.h"
#include "eigL4x4real_rtwutil.h"
#include "rt_nonfinite.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "xztgevc.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : creal_T A[16]
 *                int *info
 *                creal_T alpha1[4]
 *                creal_T beta1[4]
 *                creal_T V[16]
 * Return Type  : void
 */
void xzggev(creal_T A[16], int *info, creal_T alpha1[4], creal_T beta1[4],
            creal_T V[16])
{
  creal_T atmp;
  double a;
  double absxk;
  double anrm;
  double anrmto;
  double cto1;
  double ctoc;
  double d;
  double d1;
  double d2;
  double d3;
  double d4;
  double stemp_im;
  int rscale[4];
  int A_tmp;
  int exitg2;
  int exitg3;
  int i;
  int ihi;
  int ii;
  int ilo;
  int j;
  int jcol;
  int jcolp1;
  int jrow;
  int nzcount;
  signed char b_I[16];
  boolean_T exitg1;
  boolean_T exitg4;
  boolean_T guard1 = false;
  boolean_T ilascl;
  boolean_T notdone;
  *info = 0;
  anrm = 0.0;
  jcol = 0;
  exitg1 = false;
  while ((!exitg1) && (jcol < 16)) {
    absxk = rt_hypotd_snf(A[jcol].re, A[jcol].im);
    if (rtIsNaN(absxk)) {
      anrm = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }
      jcol++;
    }
  }
  if (rtIsInf(anrm) || rtIsNaN(anrm)) {
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
    for (jcolp1 = 0; jcolp1 < 16; jcolp1++) {
      V[jcolp1].re = rtNaN;
      V[jcolp1].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    guard1 = false;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      anrmto = 6.7178761075670888E-139;
      ilascl = true;
      guard1 = true;
    } else if (anrm > 1.4885657073574029E+138) {
      anrmto = 1.4885657073574029E+138;
      ilascl = true;
      guard1 = true;
    }
    if (guard1) {
      absxk = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        stemp_im = absxk * 2.0041683600089728E-292;
        cto1 = ctoc / 4.9896007738368E+291;
        if ((stemp_im > ctoc) && (ctoc != 0.0)) {
          a = 2.0041683600089728E-292;
          absxk = stemp_im;
        } else if (cto1 > absxk) {
          a = 4.9896007738368E+291;
          ctoc = cto1;
        } else {
          a = ctoc / absxk;
          notdone = false;
        }
        for (jcolp1 = 0; jcolp1 < 16; jcolp1++) {
          A[jcolp1].re *= a;
          A[jcolp1].im *= a;
        }
      }
    }
    rscale[0] = 1;
    rscale[1] = 1;
    rscale[2] = 1;
    rscale[3] = 1;
    ilo = 1;
    ihi = 4;
    do {
      exitg3 = 0;
      i = 0;
      j = 0;
      notdone = false;
      ii = ihi;
      exitg1 = false;
      while ((!exitg1) && (ii > 0)) {
        nzcount = 0;
        i = ii;
        j = ihi;
        jcol = 0;
        exitg4 = false;
        while ((!exitg4) && (jcol <= ihi - 1)) {
          A_tmp = (ii + (jcol << 2)) - 1;
          if ((A[A_tmp].re != 0.0) || (A[A_tmp].im != 0.0) ||
              (ii == jcol + 1)) {
            if (nzcount == 0) {
              j = jcol + 1;
              nzcount = 1;
              jcol++;
            } else {
              nzcount = 2;
              exitg4 = true;
            }
          } else {
            jcol++;
          }
        }
        if (nzcount < 2) {
          notdone = true;
          exitg1 = true;
        } else {
          ii--;
        }
      }
      if (!notdone) {
        exitg3 = 2;
      } else {
        if (i != ihi) {
          atmp = A[i - 1];
          A[i - 1] = A[ihi - 1];
          A[ihi - 1] = atmp;
          atmp = A[i + 3];
          A[i + 3] = A[ihi + 3];
          A[ihi + 3] = atmp;
          atmp = A[i + 7];
          A[i + 7] = A[ihi + 7];
          A[ihi + 7] = atmp;
          atmp = A[i + 11];
          A[i + 11] = A[ihi + 11];
          A[ihi + 11] = atmp;
        }
        if (j != ihi) {
          for (jcol = 0; jcol < ihi; jcol++) {
            ii = jcol + ((j - 1) << 2);
            atmp = A[ii];
            jcolp1 = jcol + ((ihi - 1) << 2);
            A[ii] = A[jcolp1];
            A[jcolp1] = atmp;
          }
        }
        rscale[ihi - 1] = j;
        ihi--;
        if (ihi == 1) {
          rscale[0] = 1;
          exitg3 = 1;
        }
      }
    } while (exitg3 == 0);
    if (exitg3 != 1) {
      do {
        exitg2 = 0;
        i = 0;
        j = 0;
        notdone = false;
        jcol = ilo;
        exitg1 = false;
        while ((!exitg1) && (jcol <= ihi)) {
          nzcount = 0;
          i = ihi;
          j = jcol;
          ii = ilo;
          exitg4 = false;
          while ((!exitg4) && (ii <= ihi)) {
            A_tmp = (ii + ((jcol - 1) << 2)) - 1;
            if ((A[A_tmp].re != 0.0) || (A[A_tmp].im != 0.0) || (ii == jcol)) {
              if (nzcount == 0) {
                i = ii;
                nzcount = 1;
                ii++;
              } else {
                nzcount = 2;
                exitg4 = true;
              }
            } else {
              ii++;
            }
          }
          if (nzcount < 2) {
            notdone = true;
            exitg1 = true;
          } else {
            jcol++;
          }
        }
        if (!notdone) {
          exitg2 = 1;
        } else {
          if (i != ilo) {
            for (jcol = ilo; jcol < 5; jcol++) {
              ii = (jcol - 1) << 2;
              nzcount = (i + ii) - 1;
              atmp = A[nzcount];
              jcolp1 = (ilo + ii) - 1;
              A[nzcount] = A[jcolp1];
              A[jcolp1] = atmp;
            }
          }
          if (j != ilo) {
            for (jcol = 0; jcol < ihi; jcol++) {
              ii = jcol + ((j - 1) << 2);
              atmp = A[ii];
              jcolp1 = jcol + ((ilo - 1) << 2);
              A[ii] = A[jcolp1];
              A[jcolp1] = atmp;
            }
          }
          rscale[ilo - 1] = j;
          ilo++;
          if (ilo == ihi) {
            rscale[ilo - 1] = ilo;
            exitg2 = 1;
          }
        }
      } while (exitg2 == 0);
    }
    for (jcolp1 = 0; jcolp1 < 16; jcolp1++) {
      b_I[jcolp1] = 0;
    }
    b_I[0] = 1;
    b_I[5] = 1;
    b_I[10] = 1;
    b_I[15] = 1;
    for (jcolp1 = 0; jcolp1 < 16; jcolp1++) {
      V[jcolp1].re = b_I[jcolp1];
      V[jcolp1].im = 0.0;
    }
    if (ihi >= ilo + 2) {
      for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
        jcolp1 = jcol + 2;
        for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
          A_tmp = jrow + (jcol << 2);
          xzlartg(A[A_tmp - 1], A[A_tmp], &absxk, &atmp,
                  &A[(jrow + (jcol << 2)) - 1]);
          A[A_tmp].re = 0.0;
          A[A_tmp].im = 0.0;
          for (j = jcolp1; j < 5; j++) {
            nzcount = jrow + ((j - 1) << 2);
            ctoc = absxk * A[nzcount - 1].re +
                   (atmp.re * A[nzcount].re - atmp.im * A[nzcount].im);
            stemp_im = absxk * A[nzcount - 1].im +
                       (atmp.re * A[nzcount].im + atmp.im * A[nzcount].re);
            d = A[nzcount - 1].im;
            d1 = A[nzcount - 1].re;
            A[nzcount].re =
                absxk * A[nzcount].re -
                (atmp.re * A[nzcount - 1].re + atmp.im * A[nzcount - 1].im);
            A[nzcount].im =
                absxk * A[nzcount].im - (atmp.re * d - atmp.im * d1);
            A[nzcount - 1].re = ctoc;
            A[nzcount - 1].im = stemp_im;
          }
          atmp.re = -atmp.re;
          atmp.im = -atmp.im;
          for (i = 1; i <= ihi; i++) {
            nzcount = (i + ((jrow - 1) << 2)) - 1;
            ii = (i + (jrow << 2)) - 1;
            ctoc = absxk * A[ii].re +
                   (atmp.re * A[nzcount].re - atmp.im * A[nzcount].im);
            stemp_im = absxk * A[ii].im +
                       (atmp.re * A[nzcount].im + atmp.im * A[nzcount].re);
            d = A[ii].im;
            d1 = A[ii].re;
            A[nzcount].re = absxk * A[nzcount].re -
                            (atmp.re * A[ii].re + atmp.im * A[ii].im);
            A[nzcount].im =
                absxk * A[nzcount].im - (atmp.re * d - atmp.im * d1);
            A[ii].re = ctoc;
            A[ii].im = stemp_im;
          }
          nzcount = (jrow - 1) << 2;
          ii = jrow << 2;
          ctoc = absxk * V[ii].re +
                 (atmp.re * V[nzcount].re - atmp.im * V[nzcount].im);
          stemp_im = absxk * V[ii].im +
                     (atmp.re * V[nzcount].im + atmp.im * V[nzcount].re);
          d = V[ii].re;
          V[nzcount].re =
              absxk * V[nzcount].re - (atmp.re * V[ii].re + atmp.im * V[ii].im);
          V[nzcount].im =
              absxk * V[nzcount].im - (atmp.re * V[ii].im - atmp.im * d);
          V[ii].re = ctoc;
          V[ii].im = stemp_im;
          ctoc = absxk * V[ii + 1].re +
                 (atmp.re * V[nzcount + 1].re - atmp.im * V[nzcount + 1].im);
          stemp_im = absxk * V[ii + 1].im + (atmp.re * V[nzcount + 1].im +
                                             atmp.im * V[nzcount + 1].re);
          d = V[ii + 1].re;
          V[nzcount + 1].re = absxk * V[nzcount + 1].re -
                              (atmp.re * V[ii + 1].re + atmp.im * V[ii + 1].im);
          V[nzcount + 1].im = absxk * V[nzcount + 1].im -
                              (atmp.re * V[ii + 1].im - atmp.im * d);
          V[ii + 1].re = ctoc;
          V[ii + 1].im = stemp_im;
          ctoc = absxk * V[ii + 2].re +
                 (atmp.re * V[nzcount + 2].re - atmp.im * V[nzcount + 2].im);
          stemp_im = absxk * V[ii + 2].im + (atmp.re * V[nzcount + 2].im +
                                             atmp.im * V[nzcount + 2].re);
          d = V[ii + 2].re;
          V[nzcount + 2].re = absxk * V[nzcount + 2].re -
                              (atmp.re * V[ii + 2].re + atmp.im * V[ii + 2].im);
          V[nzcount + 2].im = absxk * V[nzcount + 2].im -
                              (atmp.re * V[ii + 2].im - atmp.im * d);
          V[ii + 2].re = ctoc;
          V[ii + 2].im = stemp_im;
          ctoc = absxk * V[ii + 3].re +
                 (atmp.re * V[nzcount + 3].re - atmp.im * V[nzcount + 3].im);
          stemp_im = absxk * V[ii + 3].im + (atmp.re * V[nzcount + 3].im +
                                             atmp.im * V[nzcount + 3].re);
          d = V[ii + 3].re;
          V[nzcount + 3].re = absxk * V[nzcount + 3].re -
                              (atmp.re * V[ii + 3].re + atmp.im * V[ii + 3].im);
          V[nzcount + 3].im = absxk * V[nzcount + 3].im -
                              (atmp.re * V[ii + 3].im - atmp.im * d);
          V[ii + 3].re = ctoc;
          V[ii + 3].im = stemp_im;
        }
      }
    }
    xzhgeqz(A, ilo, ihi, V, info, alpha1, beta1);
    if (*info == 0) {
      xztgevc(A, V);
      if (ilo > 1) {
        for (i = ilo - 2; i + 1 >= 1; i--) {
          jcol = rscale[i] - 1;
          if (rscale[i] != i + 1) {
            atmp = V[i];
            V[i] = V[jcol];
            V[jcol] = atmp;
            atmp = V[i + 4];
            V[i + 4] = V[jcol + 4];
            V[jcol + 4] = atmp;
            atmp = V[i + 8];
            V[i + 8] = V[jcol + 8];
            V[jcol + 8] = atmp;
            atmp = V[i + 12];
            V[i + 12] = V[jcol + 12];
            V[jcol + 12] = atmp;
          }
        }
      }
      if (ihi < 4) {
        jcolp1 = ihi + 1;
        for (i = jcolp1; i < 5; i++) {
          ii = rscale[i - 1];
          if (ii != i) {
            atmp = V[i - 1];
            V[i - 1] = V[ii - 1];
            V[ii - 1] = atmp;
            atmp = V[i + 3];
            V[i + 3] = V[ii + 3];
            V[ii + 3] = atmp;
            atmp = V[i + 7];
            V[i + 7] = V[ii + 7];
            V[ii + 7] = atmp;
            atmp = V[i + 11];
            V[i + 11] = V[ii + 11];
            V[ii + 11] = atmp;
          }
        }
      }
      for (nzcount = 0; nzcount < 4; nzcount++) {
        ii = nzcount << 2;
        d = V[ii].re;
        d1 = V[ii].im;
        absxk = fabs(d) + fabs(d1);
        ctoc = V[ii + 1].re;
        stemp_im = V[ii + 1].im;
        cto1 = fabs(ctoc) + fabs(stemp_im);
        if (cto1 > absxk) {
          absxk = cto1;
        }
        a = V[ii + 2].re;
        d2 = V[ii + 2].im;
        cto1 = fabs(a) + fabs(d2);
        if (cto1 > absxk) {
          absxk = cto1;
        }
        d3 = V[ii + 3].re;
        d4 = V[ii + 3].im;
        cto1 = fabs(d3) + fabs(d4);
        if (cto1 > absxk) {
          absxk = cto1;
        }
        if (absxk >= 6.7178761075670888E-139) {
          absxk = 1.0 / absxk;
          d *= absxk;
          V[ii].re = d;
          d1 *= absxk;
          V[ii].im = d1;
          ctoc *= absxk;
          V[ii + 1].re = ctoc;
          stemp_im *= absxk;
          V[ii + 1].im = stemp_im;
          a *= absxk;
          V[ii + 2].re = a;
          d2 *= absxk;
          V[ii + 2].im = d2;
          d3 *= absxk;
          V[ii + 3].re = d3;
          d4 *= absxk;
          V[ii + 3].im = d4;
        }
      }
      if (ilascl) {
        notdone = true;
        while (notdone) {
          stemp_im = anrmto * 2.0041683600089728E-292;
          cto1 = anrm / 4.9896007738368E+291;
          if ((stemp_im > anrm) && (anrm != 0.0)) {
            a = 2.0041683600089728E-292;
            anrmto = stemp_im;
          } else if (cto1 > anrmto) {
            a = 4.9896007738368E+291;
            anrm = cto1;
          } else {
            a = anrm / anrmto;
            notdone = false;
          }
          alpha1[0].re *= a;
          alpha1[0].im *= a;
          alpha1[1].re *= a;
          alpha1[1].im *= a;
          alpha1[2].re *= a;
          alpha1[2].im *= a;
          alpha1[3].re *= a;
          alpha1[3].im *= a;
        }
      }
    }
  }
}

/*
 * File trailer for xzggev.c
 *
 * [EOF]
 */
