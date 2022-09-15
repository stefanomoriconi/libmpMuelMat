/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: xzlarf.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 19-Jul-2022 14:47:38
 */

/* Include Files */
#include "xzlarf.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                const creal_T tau
 *                creal_T C[16]
 *                int ic0
 *                creal_T work[4]
 * Return Type  : void
 */
void xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[16], int ic0,
            creal_T work[4])
{
  double C_im;
  double c_im;
  double c_re;
  double temp_im;
  double temp_re;
  int b_i;
  int c_re_tmp;
  int exitg1;
  int i;
  int ia;
  int iac;
  int lastc;
  int lastv;
  boolean_T exitg2;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    lastv = m;
    i = iv0 + m;
    while ((lastv > 0) && ((C[i - 2].re == 0.0) && (C[i - 2].im == 0.0))) {
      lastv--;
      i--;
    }
    lastc = n - 1;
    exitg2 = false;
    while ((!exitg2) && (lastc + 1 > 0)) {
      i = ic0 + (lastc << 2);
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= (i + lastv) - 1) {
          if ((C[ia - 1].re != 0.0) || (C[ia - 1].im != 0.0)) {
            exitg1 = 1;
          } else {
            ia++;
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
    lastv = 0;
    lastc = -1;
  }
  if (lastv > 0) {
    if (lastc + 1 != 0) {
      if (0 <= lastc) {
        memset(&work[0], 0, (lastc + 1) * sizeof(creal_T));
      }
      b_i = ic0 + (lastc << 2);
      for (iac = ic0; iac <= b_i; iac += 4) {
        c_re = 0.0;
        c_im = 0.0;
        i = (iac + lastv) - 1;
        for (ia = iac; ia <= i; ia++) {
          c_re_tmp = ((iv0 + ia) - iac) - 1;
          c_re += C[ia - 1].re * C[c_re_tmp].re + C[ia - 1].im * C[c_re_tmp].im;
          c_im += C[ia - 1].re * C[c_re_tmp].im - C[ia - 1].im * C[c_re_tmp].re;
        }
        i = (iac - ic0) >> 2;
        work[i].re += c_re - 0.0 * c_im;
        work[i].im += c_im + 0.0 * c_re;
      }
    }
    c_re = -tau.re;
    c_im = -tau.im;
    if ((!(-tau.re == 0.0)) || (!(-tau.im == 0.0))) {
      i = ic0;
      for (iac = 0; iac <= lastc; iac++) {
        if ((work[iac].re != 0.0) || (work[iac].im != 0.0)) {
          temp_re = work[iac].re * c_re + work[iac].im * c_im;
          temp_im = work[iac].re * c_im - work[iac].im * c_re;
          b_i = lastv + i;
          for (ia = i; ia < b_i; ia++) {
            c_re_tmp = ((iv0 + ia) - i) - 1;
            C_im = C[c_re_tmp].re * temp_im + C[c_re_tmp].im * temp_re;
            C[ia - 1].re += C[c_re_tmp].re * temp_re - C[c_re_tmp].im * temp_im;
            C[ia - 1].im += C_im;
          }
        }
        i += 4;
      }
    }
  }
}

/*
 * File trailer for xzlarf.c
 *
 * [EOF]
 */
