/* compile this with -gnu99 (clock_gettime throws an error without it) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#define BILLION 1000000000

FILE *fileout;
const char outputFilename[] = "temp.txt";


/*generate a list of random doubles within the interval [-bound, bound], length 'size'*/
float* generate_random_list(uint64_t size, double bound){
  float* ret = malloc(sizeof(float)*size);
  for(uint64_t i=0; i<size; i++){
    float x = (float)rand()/(float)(RAND_MAX/(2*bound)); /*generates a number in [0,2*bound]*/
      x = bound - x;
      ret[i]= x;
     }
  return ret;
}

/*update location by velocity, one time-step*/
void update_coords(uint64_t size, float* x, float* y, float* z, float* vx, float* vy, float* vz)
{
  for(uint64_t i=0; i<size; i++)
  {
    x[i] += vx[i];
    y[i] += vy[i];
    z[i] += vz[i];
  }
}


int main(int argc, char** argv){
  if(argc < 3){
    printf("args: <size> <iters>\n");
    return -1;
  }
  uint64_t size = 1 << atoi(argv[1]);
  uint64_t iters = 1 << atoi(argv[2]);

  srand(size);


  float* x = generate_random_list(size,1000.);
  float* y = generate_random_list(size,1000.);
  float* z = generate_random_list(size,1.);
  float* vx = generate_random_list(size,1.);
  float* vy = generate_random_list(size,1.);
  float* vz = generate_random_list(size,1.);

  struct timespec start,end;
  clock_gettime(CLOCK_MONOTONIC, &start);

  for (uint64_t i=0; i < iters; i++) update_coords(size,x,y,z,vx,vy,vz);
  
  clock_gettime(CLOCK_MONOTONIC, &end);

  float elapsed = (end.tv_sec * BILLION + end.tv_nsec) - (start.tv_sec * BILLION + start.tv_nsec);
  float avg = elapsed/(size * iters);
  int checksum = 0;
  for (uint64_t i=0; i<size; i++){
    checksum += x[i] + y[i] + z[i];
  }

  fileout = fopen(outputFilename, "a"); 
  fprintf(fileout, "%f\n",avg);
  fclose(fileout);
  printf("checksum is %d\n",checksum);
  printf("Average Elapsed Time: %fns\n",avg);
  return 0;
}
