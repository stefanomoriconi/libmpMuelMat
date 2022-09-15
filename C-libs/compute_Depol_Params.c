/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_Depol_Params.c
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Jul-2022 16:27:11
 */

/* Include Files */
#include "compute_Depol_Params.h"
#include <math.h>

/* Function Definitions */
/*
 * *Inputs*
 *  d22 = Mdelta(2,2);
 *  d33 = Mdelta(3,3);
 *  d44 = Mdelta(4,4);
 *  where Mdelta is the Depolarisation Matrix.
 *
 *  *Outputs*
 *  totP: total depolarisation
 *
 * Arguments    : double d22
 *                double d33
 *                double d44
 * Return Type  : double
 */
double compute_Depol_Params(double d22, double d33, double d44)
{
  return 1.0 - ((fabs(d22) + fabs(d33)) + fabs(d44)) / 3.0;
}

/*
 * File trailer for compute_Depol_Params.c
 *
 * [EOF]
 */
