#include <omp.h>
#include <stdbool.h>
#include "mp_comp_MM_AIW.h"
#include "compute_M_AIW.h"

void mp_comp_MM_AIW(double *M_out, double *nM_out, 
                    double *A_in , double *I_in , double *W_in ,
                    int *idx_in, int *numel_in  )
{
  int m = 16;
	#pragma omp parallel for 
    for (int i=0; i<numel_in[0]; ++i) // for each pixel
      {
        // Components MUST be Transposed!
        compute_M_AIW( A_in[idx_in[i]*m+0]   , A_in[idx_in[i]*m+4]   , A_in[idx_in[i]*m+8]    , A_in[idx_in[i]*m+12],
                       A_in[idx_in[i]*m+1]   , A_in[idx_in[i]*m+5]   , A_in[idx_in[i]*m+9]    , A_in[idx_in[i]*m+13],
                       A_in[idx_in[i]*m+2]   , A_in[idx_in[i]*m+6]   , A_in[idx_in[i]*m+10]   , A_in[idx_in[i]*m+14],
                       A_in[idx_in[i]*m+3]   , A_in[idx_in[i]*m+7]   , A_in[idx_in[i]*m+11]   , A_in[idx_in[i]*m+15],
                       I_in[idx_in[i]*m+0]   , I_in[idx_in[i]*m+4]   , I_in[idx_in[i]*m+8]    , I_in[idx_in[i]*m+12],
                       I_in[idx_in[i]*m+1]   , I_in[idx_in[i]*m+5]   , I_in[idx_in[i]*m+9]    , I_in[idx_in[i]*m+13],
                       I_in[idx_in[i]*m+2]   , I_in[idx_in[i]*m+6]   , I_in[idx_in[i]*m+10]   , I_in[idx_in[i]*m+14],
                       I_in[idx_in[i]*m+3]   , I_in[idx_in[i]*m+7]   , I_in[idx_in[i]*m+11]   , I_in[idx_in[i]*m+15],
                       W_in[idx_in[i]*m+0]   , W_in[idx_in[i]*m+4]   , W_in[idx_in[i]*m+8]    , W_in[idx_in[i]*m+12],
                       W_in[idx_in[i]*m+1]   , W_in[idx_in[i]*m+5]   , W_in[idx_in[i]*m+9]    , W_in[idx_in[i]*m+13],
                       W_in[idx_in[i]*m+2]   , W_in[idx_in[i]*m+6]   , W_in[idx_in[i]*m+10]   , W_in[idx_in[i]*m+14],
                       W_in[idx_in[i]*m+3]   , W_in[idx_in[i]*m+7]   , W_in[idx_in[i]*m+11]   , W_in[idx_in[i]*m+15],
                       &M_out[idx_in[i]*m+0] , &M_out[idx_in[i]*m+4] , &M_out[idx_in[i]*m+8]  , &M_out[idx_in[i]*m+12],
                       &M_out[idx_in[i]*m+1] , &M_out[idx_in[i]*m+5] , &M_out[idx_in[i]*m+9]  , &M_out[idx_in[i]*m+13],
                       &M_out[idx_in[i]*m+2] , &M_out[idx_in[i]*m+6] , &M_out[idx_in[i]*m+10] , &M_out[idx_in[i]*m+14],
                       &M_out[idx_in[i]*m+3] , &M_out[idx_in[i]*m+7] , &M_out[idx_in[i]*m+11] , &M_out[idx_in[i]*m+15] );

      } // End of #pragma omp parallel for (parallel)
  #pragma omp parallel for 
    for (int i=0; i<numel_in[0]; ++i) // for each pixel
      {
        nM_out[idx_in[i]*m+0] = 1.0;
        nM_out[idx_in[i]*m+1] = M_out[idx_in[i]*m+1] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+2] = M_out[idx_in[i]*m+2] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+3] = M_out[idx_in[i]*m+3] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+4] = M_out[idx_in[i]*m+4] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+5] = M_out[idx_in[i]*m+5] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+6] = M_out[idx_in[i]*m+6] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+7] = M_out[idx_in[i]*m+7] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+8] = M_out[idx_in[i]*m+8] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+9] = M_out[idx_in[i]*m+9] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+10] = M_out[idx_in[i]*m+10] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+11] = M_out[idx_in[i]*m+11] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+12] = M_out[idx_in[i]*m+12] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+13] = M_out[idx_in[i]*m+13] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+14] = M_out[idx_in[i]*m+14] / M_out[idx_in[i]*m+0];
        nM_out[idx_in[i]*m+15] = M_out[idx_in[i]*m+15] / M_out[idx_in[i]*m+0];
      }
}