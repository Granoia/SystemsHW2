/* compile this with -gnu99 (clock_gettime throws an error without it) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#define BILLION 1000000000

FILE *fileout;
const char outputFilename[] = "temp.txt";


/*generate a list of random doubles within the interval [-bound, bound], length 'size'*/
double* generate_random_list(uint64_t size, double bound){
  double* ret = malloc(sizeof(double)*size);
  for(uint64_t i=0; i<size; i++){
    double x = (double)rand()/(double)(RAND_MAX/(2*bound)); /*generates a number in [0,2*bound]*/
      x = bound - x;
      ret[i]= x;
     }
  return ret;
}

/*update location by velocity, one time-step*/
void update_coords(uint64_t size, double* x, double* y, double* z, double* vx, double* vy, double* vz)
{
  asm(   "movq $0, %%rdi; "

	 ".cond: "
	 "cmpq %0, %%rdi; "
	 "jge .end; "

	 "movsd (%1,%%rdi,8), %%xmm0; "
	 "addsd (%2,%%rdi,8), %%xmm0; "
	 "movsd %%xmm0, (%1,%%rdi,8); "
	 "addq $1, %%rdi; "
	 "jmp .cond; "
	 ".end: "
	 :
	 :"r"(size),"r"(x), "r"(vx), "r"(y), "r"(vy), "r"(z), "r"(vz)
	 :"%rdi","%rdx","%xmm0"
	 );
}


int main(int argc, char** argv){

if(argc < 3){
    printf("args: <size> <iters>\n");
    return -1;
  }
  int size = 1 << atoi(argv[1]);
  int iters = 1 << atoi(argv[2]);
  srand(size);

  double* x = generate_random_list(size,1000.);
  double* y = generate_random_list(size,1000.);
  double* z = generate_random_list(size,1.);
  double* vx = generate_random_list(size,1.);
  double* vy = generate_random_list(size,1.);
  double* vz = generate_random_list(size,1.);

  for (int i=0; i < size; i++) printf("%f, ",x[i]);
  printf("\n");
  for (int i=0; i < size; i++) printf("%f, ",vx[i]);
  printf("\n");
  update_coords(size,x,y,z,vx,vy,vz);
  printf("Updated.\n");
 for (int i=0; i < size; i++) printf("%f, ",x[i]);
  printf("\n");
  for (int i=0; i < size; i++) printf("%f, ",vx[i]);
  printf("\n\n");
  return 0;

  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  for (uint64_t i=0; i < iters; i++) update_coords(size,x,y,z,vx,vy,vz);
  
  clock_gettime(CLOCK_MONOTONIC, &end);

  double elapsed = (end.tv_sec * BILLION + end.tv_nsec) - (start.tv_sec * BILLION + start.tv_nsec);
  double avg = elapsed/(double)(size * iters);
  int checksum = 0;
  for (int i=0; i<size; i++){
    checksum += x[i] + y[i] + z[i];
  }


  fileout = fopen(outputFilename, "a"); 
  fprintf(fileout, "%f\n",avg);
  fclose(fileout);
  printf("checksum is %d\n",checksum);
  printf("Average Elapsed Time: %fus\n",avg);
  return 0;
}
