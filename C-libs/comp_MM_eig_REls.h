#ifndef comp_MM_eig_REls_h__
#define comp_MM_eig_REls_h__
/* Function Declarations */
void comp_MM_eig_REls( double *el1R ,double *el2R ,double *el3R ,double *el4R ,
                       bool   *elRmsk,
                       double *m11, double *m12, double *m13, double *m14,
                       double *m21, double *m22, double *m23, double *m24,
                       double *m31, double *m32, double *m33, double *m34,
                       double *m41, double *m42, double *m43, double *m44,
                       double *nMag,double *elR_thr);
#endif