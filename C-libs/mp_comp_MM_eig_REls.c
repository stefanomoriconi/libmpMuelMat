#include <omp.h>
#include <stdbool.h>
#include "mp_comp_MM_eig_REls.h"
#include "comp_MM_eig_REls.h"

void mp_comp_MM_eig_REls( double *elsR_out , bool *elsRmsk_out,
                          double *M_in , double *nMag   , double *elsR_thr,
                          int *idx_in    , int *numel_in  )
{
  // double ref_m11 = 1.0; // it was in the original code ...
  // NB: It is assumed *NORMALISED* Mueller Matrix coefficients as input! i.e. m11 equal to 1.0 everywhere
  int l = 4; 
  int m = 16;
  #pragma omp parallel for 
    for (int i=0; i<numel_in[0]; ++i) // for each pixel
      {
      	comp_MM_eig_REls( &elsR_out[idx_in[i]*l+0] , &elsR_out[idx_in[i]*l+1] , &elsR_out[idx_in[i]*l+2] , &elsR_out[idx_in[i]*l+3],
                          &elsRmsk_out[idx_in[i]] ,
                          &M_in[idx_in[i]*m+0]     , &M_in[idx_in[i]*m+1]     , &M_in[idx_in[i]*m+2]     , &M_in[idx_in[i]*m+3],
      							      &M_in[idx_in[i]*m+4]     , &M_in[idx_in[i]*m+5]     , &M_in[idx_in[i]*m+6]     , &M_in[idx_in[i]*m+7],
      							      &M_in[idx_in[i]*m+8]     , &M_in[idx_in[i]*m+9]     , &M_in[idx_in[i]*m+10]    , &M_in[idx_in[i]*m+11],
      							      &M_in[idx_in[i]*m+12]    , &M_in[idx_in[i]*m+13]    , &M_in[idx_in[i]*m+14]    , &M_in[idx_in[i]*m+15],
                          nMag, elsR_thr );
      }
}