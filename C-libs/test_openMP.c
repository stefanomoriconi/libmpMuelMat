#ifndef test_openMP_h__
#define test_openMP_h__
/* Function Declarations */
void test_openMP();
#endif

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void test_openMP()
{
  printf(" Testing parallel-computing (openMP) libraries:... \n\n");
  printf(" >> ");
  #pragma omp parallel for 
    for (int i=0; i<10; ++i)
      {
        printf("%d ",i);
      }
      printf("\n");
}