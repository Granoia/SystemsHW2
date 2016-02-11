#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

void main()
{
  double* a = malloc(sizeof(double));
  int* b = malloc(sizeof(int)*1);

  a[0] = 1;

  asm("movl $1, (%0); "
      "movabsq	$4607182418800017408, %%rax; "
      "movq %%rax, (%1)"
      :
      :"r"(b), "r"(a)
      :
      );
  printf("%d\n",b[0]);
  printf("%f\n",a[0]);

}
