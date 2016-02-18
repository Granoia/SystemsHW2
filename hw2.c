#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BILLION 1000000000

uint8_t* make_buffer(int len)
{
  uint8_t* ret = malloc(8*len);
  for (int i=0; i < len; i++)
    {
      ret[i] = rand() % (1<<8 - 1);
    }
  return ret;
}

void access_at_random(uint8_t* buffer, int size)
{
  uint8_t datum = buffer[0];
  for (int i=0; i < size; i++)
    {
      datum = buffer[datum];
    }
  buffer[0] = datum;
  printf("%d\n",datum);
}



int main(int argc, char** argv)
{
  if (argc != 3) printf("%s <size> <iters>\n",argv[0]);

  const int size = atoi(argv[1]);
  const int iters = atoi(argv[2]);
  srand(time(NULL));
  struct timespec begin;
  struct timespec end;

  uint8_t* buffer = make_buffer(size);
  printf("Buffer loaded.\n");

  clock_gettime(CLOCK_MONOTONIC, &begin);
  for (int i=0; i < iters; i++) 
  {
    access_at_random(buffer, size);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);

  int duration = BILLION*(end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
  printf("Duration: %d",duration);
  printf("\n");
}
