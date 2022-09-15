/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include "compute_det4x4real.h"

void compute_det4x4real(double *d,
                        double *a11, double *a12, double *a13, double *a14,
                        double *a21, double *a22, double *a23, double *a24,
                        double *a31, double *a32, double *a33, double *a34,
                        double *a41, double *a42, double *a43, double *a44)
{
 *d = 
	*a11**a22**a33**a44 - *a11**a22**a34**a43 - *a11**a23**a32**a44 + *a11**a23**a34**a42 + 
	*a11**a24**a32**a43 - *a11**a24**a33**a42 - *a12**a21**a33**a44 + *a12**a21**a34**a43 + 
	*a12**a23**a31**a44 - *a12**a23**a34**a41 - *a12**a24**a31**a43 + *a12**a24**a33**a41 + 
	*a13**a21**a32**a44 - *a13**a21**a34**a42 - *a13**a22**a31**a44 + *a13**a22**a34**a41 + 
	*a13**a24**a31**a42 - *a13**a24**a32**a41 - *a14**a21**a32**a43 + *a14**a21**a33**a42 + 
	*a14**a22**a31**a43 - *a14**a22**a33**a41 - *a14**a23**a31**a42 + *a14**a23**a32**a41;
}