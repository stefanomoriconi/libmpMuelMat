#include <omp.h>
#include <stdbool.h>
#include "mp_comp_MM_polarim_Params.h"
#include "compute_Depol_Params.h"
#include "compute_Diatt_Params.h"
#include "compute_Retard_Params.h"

void mp_comp_MM_polarim_Params( double *totD_out, double *linD_out, double *oriD_out, double *cirD_out,
                                double *totR_out, double *linR_out, double *cirR_out, double *oriR_out, double *oriRfull_out,
                                double *totP_out,
                                double *MD_in, double *MR_in, double *Mdelta_in,
                                int    *idx_in, int *numel_in )
{
  int m = 16;
	#pragma omp parallel for 
    for (int i=0; i<numel_in[0]; ++i) // for each pixel
      {
        compute_Diatt_Params( MD_in[idx_in[i]*m+4], MD_in[idx_in[i]*m+8], MD_in[idx_in[i]*m+12],
                              &totD_out[idx_in[i]], &linD_out[idx_in[i]], &oriD_out[idx_in[i]], &cirD_out[idx_in[i]] ); //t12,t13,t14 (TRANSPOSED)

        compute_Retard_Params( MR_in[idx_in[i]*m+0] ,  MR_in[idx_in[i]*m+4] ,  MR_in[idx_in[i]*m+8] ,  MR_in[idx_in[i]*m+12],
                               MR_in[idx_in[i]*m+1] ,  MR_in[idx_in[i]*m+5] ,  MR_in[idx_in[i]*m+9] ,  MR_in[idx_in[i]*m+13],
                               MR_in[idx_in[i]*m+2] ,  MR_in[idx_in[i]*m+6] ,  MR_in[idx_in[i]*m+10],  MR_in[idx_in[i]*m+14],
                               MR_in[idx_in[i]*m+3] ,  MR_in[idx_in[i]*m+7] ,  MR_in[idx_in[i]*m+11],  MR_in[idx_in[i]*m+15],
                               &totR_out[idx_in[i]] ,  &linR_out[idx_in[i]] ,  &cirR_out[idx_in[i]],
                               &oriR_out[idx_in[i]] ,  &oriRfull_out[idx_in[i]]); // (TRANSPOSED)

        totP_out[idx_in[i]] = compute_Depol_Params( Mdelta_in[idx_in[i]*m+5], 
                                                    Mdelta_in[idx_in[i]*m+10], 
                                                    Mdelta_in[idx_in[i]*m+15] ); // d22,d33,d44
      }
}