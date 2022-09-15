/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_Diatt_Params.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Jul-2022 16:28:25
 */

/* Include Files */
#include "compute_Diatt_Params.h"
#include <math.h>

/* Function Definitions */
/*
 * *Inputs*
 *  t12 = MD(1,2);
 *  t13 = MD(1,3);
 *  t14 = MD(1,4);
 *  where MD is the Diattenuation Matrix.
 *
 *  *Outputs*
 *  totD: total diattenuation
 *  linD: linear diattenuation
 *  oriD: orientation of the linear diattenuation
 *  cirD: circular diattenuation
 *
 * Arguments    : double t12
 *                double t13
 *                double t14
 *                double *totD
 *                double *linD
 *                double *oriD
 *                double *cirD
 * Return Type  : void
 */
void compute_Diatt_Params(double t12, double t13, double t14, 
                          double *totD, double *linD, double *oriD, double *cirD)
{
  double totD_tmp;
  /*  Diattenuation */
  totD_tmp = t12 * t12 + t13 * t13;
  *totD = sqrt(totD_tmp + t14 * t14);
  *linD = sqrt(totD_tmp);
  *oriD = 0.5 * (57.295779513082323 * atan(t13 / t12));
  *cirD = fabs(t14);
}

/*
 * File trailer for compute_Diatt_Params.c
 *
 * [EOF]
 */
