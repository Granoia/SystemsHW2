#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


uint8_t* make_buffer(int len)
{
  uint8_t* ret = malloc(8*len);
  for (int i=0; i < len; i++)
    {
      ret[i] = rand() % len;
    }
  return ret;
}


void access(uint8_t* buffer, int size)
{
  int j = 0;
  int k;
  for (int i=0; i < size; i++)
    {
      j = (j * 3 + 7) % size;
      k = buffer[j];
    }
}


int main(int argc, char** argv)
{
  if (argc != 3) 
  {
    printf("%s <2^size> <2^iters>\n",argv[0]);
    return 0;
  }

  const int size = 1 << atoi(argv[1]);
  const int iters = 1 << atoi(argv[2]);
  const int BILLION = 1000000000;
 
  //Initialization
  srand(time(NULL));
  struct timespec begin;
  struct timespec end;
  uint8_t* buffer = make_buffer(size);
  printf("Buffer loaded.\n");

  //Timing the loop
  clock_gettime(CLOCK_MONOTONIC, &begin);
  for (int i=0; i < iters; i++) 
  {
    access(buffer,size);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  free(buffer);
  //Output the time
  double duration = BILLION*(end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
  duration /= iters*size;
  printf("Duration: %fns",duration);
  printf("\n");

  //Write time to a file
  FILE* fileout = fopen("temp.txt", "a");
  fprintf(fileout, "%f\n", duration);
  fclose(fileout);

  return 0;
}
