/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include "comp_MM_eig_REls.h"
#include "eigL4x4real.h"
#include "rt_nonfinite.h"

void comp_MM_eig_REls(double *el1R ,double *el2R ,double *el3R ,double *el4R ,
                      bool   *elRmsk,
                      double *m11, double *m12, double *m13, double *m14,
                      double *m21, double *m22, double *m23, double *m24,
                      double *m31, double *m32, double *m33, double *m34,
                      double *m41, double *m42, double *m43, double *m44,
                      double *nMag,double *elR_thr)
{
 // double nMag = 0.25; // as INPUT
 double n11R,n11I,n12R,n12I,n13R,n13I,n14R,n14I,
 		  n21R,n21I,n22R,n22I,n23R,n23I,n24R,n24I,
 		  n31R,n31I,n32R,n32I,n33R,n33I,n34R,n34I,
 		  n41R,n41I,n42R,n42I,n43R,n43I,n44R,n44I;

 // Define nii_re,_im
 n11R = *nMag * ( *m11+*m22+*m12+*m21 );
 n11I = *nMag * 0.0;
 n12R = *nMag * ( *m13+*m23 ); 
 n12I = *nMag * ( *m14+*m24 );
 n13R = *nMag * ( *m31+*m32 );
 n13I = *nMag * ( *m41+*m42 ) * -1.0;
 n14R = *nMag * ( *m33+*m44 );
 n14I = *nMag * ( *m34-*m43 );

 n21R = *nMag * ( *m13+*m23 );
 n21I = *nMag * ( *m14+*m24 ) * -1.0;
 n22R = *nMag * ( *m11-*m22-*m12+*m21 );
 n22I = *nMag * 0.0;
 n23R = *nMag * ( *m33-*m44 );
 n23I = *nMag * ( *m34+*m43 ) * -1.0;
 n24R = *nMag * ( *m31-*m32 );
 n24I = *nMag * ( *m41-*m42 ) * -1.0;

 n31R = *nMag * ( *m31+*m32 );
 n31I = *nMag * ( *m41+*m42 );
 n32R = *nMag * ( *m33-*m44 ); 
 n32I = *nMag * ( *m34+*m43 );
 n33R = *nMag * ( *m11-*m22+*m12-*m21 );
 n33I = *nMag * 0.0;
 n34R = *nMag * ( *m13-*m23 );
 n34I = *nMag * ( *m14-*m24 );

 n41R = *nMag * ( *m33+*m44 );
 n41I = *nMag * ( *m34-*m43 ) * -1.0;
 n42R = *nMag * ( *m31-*m32 );
 n42I = *nMag * ( *m41-*m42 );
 n43R = *nMag * ( *m13-*m23 );
 n43I = *nMag * ( *m14-*m24 ) * -1.0;
 n44R = *nMag * ( *m11+*m22-*m12-*m21 );
 n44I = *nMag * 0.0;

 if ( rtIsInf(n11R) || rtIsNaN(n11R) || rtIsInf(n11I) || rtIsNaN(n11I) || 
 	  rtIsInf(n12R) || rtIsNaN(n12R) || rtIsInf(n12I) || rtIsNaN(n12I) || 
 	  rtIsInf(n13R) || rtIsNaN(n13R) || rtIsInf(n13I) || rtIsNaN(n13I) ||
 	  rtIsInf(n14R) || rtIsNaN(n14R) || rtIsInf(n14I) || rtIsNaN(n14I) ||
 	  rtIsInf(n21R) || rtIsNaN(n21R) || rtIsInf(n21I) || rtIsNaN(n21I) || 
 	  rtIsInf(n22R) || rtIsNaN(n22R) || rtIsInf(n22I) || rtIsNaN(n22I) || 
 	  rtIsInf(n23R) || rtIsNaN(n23R) || rtIsInf(n23I) || rtIsNaN(n23I) ||
 	  rtIsInf(n24R) || rtIsNaN(n24R) || rtIsInf(n24I) || rtIsNaN(n24I) ||
 	  rtIsInf(n31R) || rtIsNaN(n31R) || rtIsInf(n31I) || rtIsNaN(n31I) || 
 	  rtIsInf(n32R) || rtIsNaN(n32R) || rtIsInf(n32I) || rtIsNaN(n32I) || 
 	  rtIsInf(n33R) || rtIsNaN(n33R) || rtIsInf(n33I) || rtIsNaN(n33I) ||
 	  rtIsInf(n34R) || rtIsNaN(n34R) || rtIsInf(n34I) || rtIsNaN(n34I) ||
 	  rtIsInf(n41R) || rtIsNaN(n41R) || rtIsInf(n41I) || rtIsNaN(n41I) || 
 	  rtIsInf(n42R) || rtIsNaN(n42R) || rtIsInf(n42I) || rtIsNaN(n42I) || 
 	  rtIsInf(n43R) || rtIsNaN(n43R) || rtIsInf(n43I) || rtIsNaN(n43I) ||
 	  rtIsInf(n44R) || rtIsNaN(n44R) || rtIsInf(n44I) || rtIsNaN(n44I) )
 { *elRmsk = 0;}
 else
 {
 	//double elR_thr = -0.0001; // as INPUT

    eigL4x4real(n11R,n11I,n12R,n12I,n13R,n13I,n14R,n14I,
 			       n21R,n21I,n22R,n22I,n23R,n23I,n24R,n24I,
 				    n31R,n31I,n32R,n32I,n33R,n33I,n34R,n34I,
 				    n41R,n41I,n42R,n42I,n43R,n43I,n44R,n44I,
 				    el1R,el2R,el3R,el4R);

   if ( (*el1R < *elR_thr) || (*el2R < *elR_thr) || (*el3R < *elR_thr) || (*el4R < *elR_thr))
   { *elRmsk = 0; }
	else
	{ *elRmsk = 1;}

 }

}