#ifndef mp_comp_MM_eig_REls_h__
#define mp_comp_MM_eig_REls_h__
/* Function Declarations */
void mp_comp_MM_eig_REls( double *elsR_out ,bool   *elsRmsk_out,
                          double *M_in , double *nMag   , double *elsR_thr,
                          int    *idx_in , int *numel_in  );
#endif