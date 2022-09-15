/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_Retard_Params.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Jul-2022 16:50:03
 */

/* Include Files */
#include "compute_Retard_Params.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Declarations */
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */
/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }
    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }
    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }
  return y;
}

/*
 * *Inputs*
 *  p11,...p44 are components of the Phase Shift Matrix (MR).
 *
 *  *Outputs*
 *  totR: total phase shift (retardance)
 *  linR: linear phase shift (retardance)
 *  cirR: circular phase shift (retardance)
 *  oriR: orientation of the linear phase shift (retardance) [0-90]
 *  oriRfull: full orientation of the linear phase shift (retardance) [0-180]
 *
 * Arguments    : double p11
 *                double p12
 *                double p13
 *                double p14
 *                double p21
 *                double p22
 *                double p23
 *                double p24
 *                double p31
 *                double p32
 *                double p33
 *                double p34
 *                double p41
 *                double p42
 *                double p43
 *                double p44
 *                double *totR
 *                double *linR
 *                double *cirR
 *                double *oriR
 *                double *oriRfull
 * Return Type  : void
 */
void compute_Retard_Params(double p11, double p12, double p13, double p14,
                           double p21, double p22, double p23, double p24,
                           double p31, double p32, double p33, double p34,
                           double p41, double p42, double p43, double p44,
                           double *totR, double *linR, double *cirR,
                           double *oriR, double *oriRfull)
{
  double MR[16];
  double MRC[16];
  double MRL[16];
  double argu;
  double argu_tmp;
  double d;
  double d1;
  double d2;
  int i;
  int i1;
  int i2;
  /*  Retardance */
  MR[0] = p11;
  MR[4] = p12;
  MR[8] = p13;
  MR[12] = p14;
  MR[1] = p21;
  MR[5] = p22;
  MR[9] = p23;
  MR[13] = p24;
  MR[2] = p31;
  MR[6] = p32;
  MR[10] = p33;
  MR[14] = p34;
  MR[3] = p41;
  MR[7] = p42;
  MR[11] = p43;
  MR[15] = p44;
  argu_tmp = p22 + p33;
  argu = 0.5 * (argu_tmp + p44) - 0.5;
  if (fabs(argu) > 1.0) {
    if (argu > 0.0) {
      d = 0.0;
    } else {
      d = 3.1415926535897931;
    }
  } else {
    d = acos(argu);
  }
  *totR = d * 180.0 / 3.1415926535897931;
  *linR = 57.295779513082323 * acos(p44);
  *cirR = 57.295779513082323 * atan((p32 - p23) / argu_tmp);
  argu = *cirR / 2.0 * 3.1415926535897931 / 180.0;
  argu_tmp = sin(2.0 * argu);
  argu = cos(2.0 * argu);
  MRC[1] = 0.0;
  MRC[5] = argu;
  MRC[9] = -argu_tmp;
  MRC[13] = 0.0;
  MRC[2] = 0.0;
  MRC[6] = argu_tmp;
  MRC[10] = argu;
  MRC[14] = 0.0;
  MRC[0] = 1.0;
  MRC[3] = 0.0;
  MRC[4] = 0.0;
  MRC[7] = 0.0;
  MRC[8] = 0.0;
  MRC[11] = 0.0;
  MRC[12] = 0.0;
  MRC[15] = 1.0;
  argu = fabs(*cirR);
  if (argu < 0.0001) {
    memcpy(&MRL[0], &MR[0], 16U * sizeof(double));
  } else {
    /*  'LIN-CIR' mode */
    for (i = 0; i < 4; i++) {
      argu_tmp = MR[i];
      d = MR[i + 4];
      d1 = MR[i + 8];
      d2 = MR[i + 12];
      for (i1 = 0; i1 < 4; i1++) {
        MRL[i + (i1 << 2)] =
            ((argu_tmp * MRC[i1] + d * MRC[i1 + 4]) + d1 * MRC[i1 + 8]) +
            d2 * MRC[i1 + 12];
      }
    }
    if (fabs(57.295779513082323 *
             atan((MRL[6] - MRL[9]) / (MRL[5] + MRL[10]))) > argu) {
      for (i = 0; i < 4; i++) {
        argu = MR[i];
        argu_tmp = MR[i + 4];
        d = MR[i + 8];
        d1 = MR[i + 12];
        for (i1 = 0; i1 < 4; i1++) {
          i2 = i1 << 2;
          MRL[i + i2] =
              ((argu * MRC[i2] + argu_tmp * MRC[i2 + 1]) + d * MRC[i2 + 2]) +
              d1 * MRC[i2 + 3];
        }
      }
    }
  }
  *oriR = 57.295779513082323 * rt_atan2d_snf(MRL[13], MRL[11]);
  if (*oriR < 0.0) {
    *oriR = 360.0 - fabs(*oriR);
  }
  *oriRfull = 0.5 * *oriR;
  *oriR = *oriRfull + 90.0;
}

/*
 * File trailer for compute_Retard_Params.c
 *
 * [EOF]
 */
