/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 * File: compute_Retard_Params.h
 *
 * MATLAB Coder version            : 5.2
 * C/C++ source code generated on  : 29-Jul-2022 16:50:03
 */

#ifndef COMPUTE_RETARD_PARAMS_H
#define COMPUTE_RETARD_PARAMS_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void compute_Retard_Params(double p11, double p12, double p13,
                                  double p14, double p21, double p22,
                                  double p23, double p24, double p31,
                                  double p32, double p33, double p34,
                                  double p41, double p42, double p43,
                                  double p44, double *totR, double *linR,
                                  double *cirR, double *oriR, double *oriRfull);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for compute_Retard_Params.h
 *
 * [EOF]
 */
