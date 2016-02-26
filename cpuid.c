#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


int main(){
  int* regs = calloc(4, 32);
  char* whatever = regs;
  /*  whatever[32] = '\0'; */
  asm(
      "movl $2, %%eax; "
      "cpuid; "
      "movl %%eax, %0; "
      "movl %%ebx, %1; "
      "movl %%edx, %2; "
      "movl %%ecx, %3; "
      : "=r" (regs[0]), "=r" (regs[1]), "=r" (regs[2]), "=r" (regs[3])
      : 
      : "%eax","%ebx","%ecx","%edx"
      );
  printf("%02X, %02X, %02X, %02X",(unsigned char)whatever[0],(unsigned char)whatever[1],(unsigned char)whatever[2],(unsigned char)whatever[3]);
  printf("\n");
  printf("%02X, %02X, %02X, %02X",(unsigned char)whatever[4],(unsigned char)whatever[5],(unsigned char)whatever[6],(unsigned char)whatever[7]);
  printf("\n");
  printf("%02X, %02X, %02X, %02X",(unsigned char)whatever[8],(unsigned char)whatever[9],(unsigned char)whatever[10],(unsigned char)whatever[11]);
  printf("\n");
  printf("%02X, %02X, %02X, %02X",(unsigned char)whatever[12],(unsigned char)whatever[13],(unsigned char)whatever[14],(unsigned char)whatever[15]);
  printf("\n");
  return 0;
}
