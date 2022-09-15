#include <omp.h>
#include <stdbool.h>
#include "mp_comp_MM_pol_LuChipman.h"
#include "compute_MM_polarLuChipman.h"

void mp_comp_MM_pol_LuChipman( double *MD_out, double *MR_out, double *Mdelta_out,
                               double *M_in  , int    *idx_in, int *numel_in )
{
  // double ref_m11 = 1.0; // it was in the original code ...
  // NB: It is assumed *NORMALISED* Mueller Matrix coefficients as input! i.e. m11 equal to 1.0 everywhere
  int m = 16;
  #pragma omp parallel for 
    for (int i=0; i<numel_in[0]; ++i) // for each pixel
      {
        // NB: Transposed Components! (MD is symmetric?)
      	compute_MM_polarLuChipman( M_in[idx_in[i]*m+0], M_in[idx_in[i]*m+4], M_in[idx_in[i]*m+8] , M_in[idx_in[i]*m+12], 
                                   M_in[idx_in[i]*m+1], M_in[idx_in[i]*m+5], M_in[idx_in[i]*m+9] , M_in[idx_in[i]*m+13], 
                                   M_in[idx_in[i]*m+2], M_in[idx_in[i]*m+6], M_in[idx_in[i]*m+10], M_in[idx_in[i]*m+14],
                                   M_in[idx_in[i]*m+3], M_in[idx_in[i]*m+7], M_in[idx_in[i]*m+11], M_in[idx_in[i]*m+15], 
                                   &MD_out[idx_in[i]*m+0] , &MD_out[idx_in[i]*m+4] , &MD_out[idx_in[i]*m+8] , &MD_out[idx_in[i]*m+12], 
                                   &MD_out[idx_in[i]*m+1] , &MD_out[idx_in[i]*m+5] , &MD_out[idx_in[i]*m+9] , &MD_out[idx_in[i]*m+13], 
                                   &MD_out[idx_in[i]*m+2] , &MD_out[idx_in[i]*m+6] , &MD_out[idx_in[i]*m+10], &MD_out[idx_in[i]*m+14], 
                                   &MD_out[idx_in[i]*m+3] , &MD_out[idx_in[i]*m+7] , &MD_out[idx_in[i]*m+11], &MD_out[idx_in[i]*m+15], 
                                   &MR_out[idx_in[i]*m+0] , &MR_out[idx_in[i]*m+4] , &MR_out[idx_in[i]*m+8] , &MR_out[idx_in[i]*m+12], 
                                   &MR_out[idx_in[i]*m+1] , &MR_out[idx_in[i]*m+5] , &MR_out[idx_in[i]*m+9] , &MR_out[idx_in[i]*m+13], 
                                   &MR_out[idx_in[i]*m+2] , &MR_out[idx_in[i]*m+6] , &MR_out[idx_in[i]*m+10], &MR_out[idx_in[i]*m+14], 
                                   &MR_out[idx_in[i]*m+3] , &MR_out[idx_in[i]*m+7] , &MR_out[idx_in[i]*m+11], &MR_out[idx_in[i]*m+15], 
                                   &Mdelta_out[idx_in[i]*m+0] , &Mdelta_out[idx_in[i]*m+4] , &Mdelta_out[idx_in[i]*m+8] , &Mdelta_out[idx_in[i]*m+12], 
                                   &Mdelta_out[idx_in[i]*m+1] , &Mdelta_out[idx_in[i]*m+5] , &Mdelta_out[idx_in[i]*m+9] , &Mdelta_out[idx_in[i]*m+13], 
                                   &Mdelta_out[idx_in[i]*m+2] , &Mdelta_out[idx_in[i]*m+6] , &Mdelta_out[idx_in[i]*m+10], &Mdelta_out[idx_in[i]*m+14], 
                                   &Mdelta_out[idx_in[i]*m+3] , &Mdelta_out[idx_in[i]*m+7] , &Mdelta_out[idx_in[i]*m+11], &Mdelta_out[idx_in[i]*m+15] ); 
      }
}