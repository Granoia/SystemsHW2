/* compile this with -gnu99 (clock_gettime throws an error without it) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

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

void update_coords(uint64_t size, double* x, double* y, double* z, double* vx, double* vy, double* vz)
{
  for (uint64_t i=0; i < 8; i++)
    {
      asm("addq %3, %0; "
	  :"=r"(x[i]), "=r"(y[i]), "=r"(z[i])
	  :"r"(vx[i]), "r" (vy[i]), "r"(vz[i])
      :"memory");
    }
}

int main(int argc, char** argv){
  if(argc != 3){
    printf("args: <size> <iters>\n");
    return -1;
  }
  srand(time(NULL));
  int size = 1 << atoi(argv[1]);
  int iters = 1 << atoi(argv[2]);
  printf("size: %d\n",size);

  double* x = generate_random_list(size,1000.);
  double* y = generate_random_list(size,1000.);
  double* z = generate_random_list(size,1.);
  double* vx = generate_random_list(size,1.);
  double* vy = generate_random_list(size,1.);
  double* vz = generate_random_list(size,1.);

  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC, &end);

  for (uint64_t i=0; i < iters; i++) 
  {
    update_coords(size,x,y,z,vx,vy,vz);
  }  
  clock_gettime(CLOCK_MONOTONIC, &end);

  double checksum = 0;
    for (int i=0; i < size; i++) {
      printf("%f\n",x[i]);
    }

  double elapsed = end.tv_nsec - start.tv_nsec;
  double avg = elapsed/(double)(size * iters);
  printf("\nAverage Elapsed Time: %f\n",avg);
  printf("checksum: %f\n", checksum);
  return 0;
}
