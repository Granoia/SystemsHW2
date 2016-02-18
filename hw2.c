#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BILLION 1000000000

uint64_t* make_buffer(int len)
{
  uint64_t* ret = malloc(64*len);
  for (int i=0; i < len; i++)
    {
      ret[i] = rand() % len;
    }
  return ret;
}

void access_at_random(uint64_t* buffer, int size)
{
  uint64_t datum = buffer[0];
  for (int i=0; i < size; i++)
    {
      datum = buffer[datum];
    }
  buffer[0] = (datum * 15485863) % size;
  printf("%d\n",(int)datum);
}



int main(int argc, char** argv)
{
  if (argc != 3) printf("%s <2^size> <2^iters>\n",argv[0]);

  const int size = 1 << atoi(argv[1]);
  const int iters = 1 << atoi(argv[2]);
  srand(time(NULL));
  struct timespec begin;
  struct timespec end;

  uint64_t* buffer = make_buffer(size);
  printf("Buffer loaded.\n");

  clock_gettime(CLOCK_MONOTONIC, &begin);
  for (int i=0; i < iters; i++) 
  {
    access_at_random(buffer, size);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  double duration = BILLION*(end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
  duration /= iters*size;
  printf("Duration: %fns",duration);
  printf("\n");
}
