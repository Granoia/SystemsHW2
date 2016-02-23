#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BILLION 1000000000

uint8_t* make_buffer(uint64_t len)
{
  uint8_t* ret = malloc(8*len);
  for (uint64_t i=0; i < len; i++)
    {
      ret[i] = rand() % len;
    }
  return ret;
}


inline void access_at_random(uint8_t* buffer, uint64_t size,uint8_t* trash)
{
  for (uint64_t i=0; i < size; i++)
    {
      trash[i] = buffer[i];
    }
}

//Shuffles a list of ints
void shuffle(uint8_t* ls, uint64_t length){
  printf("Length of list is: %d\n", length);
  for(uint64_t i=0; i<length; i++){
    uint64_t j = rand() % (length-i);
    uint8_t a = ls[i];
    uint8_t b = ls[i+j];
    ls[i] = b;
    ls[i+j] = a;
  }
  return;
}

uint64_t main(uint64_t argc, char** argv)
{
  printf("%lu\n",sizeof(int));
  if (argc != 3) 
  {
    printf("%s <2^size> <2^iters>\n",argv[0]);
    return 0;
  }

  const uint64_t size = 1 << atoi(argv[1]);
  const uint64_t iters = 1 << atoi(argv[2]);
 
  //Initialization
  srand(time(NULL));
  struct timespec begin;
  struct timespec end;
  printf("Loading first buffer.\n");
  uint8_t* buffer = make_buffer(size);
  printf("First buffer loaded.\n");
  uint8_t* trash = malloc(8*size);
  printf("Second buffer loaded.\n");

  //Timing the loop
  clock_gettime(CLOCK_MONOTONIC, &begin);
  for (uint64_t i=0; i < iters; i++) 
  {
    access_at_random(buffer, size,trash);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  free(buffer);
  free(trash);
  //Output the time
    double duration = BILLION*(end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
    duration /= iters*size;
    printf("Duration: %fns",duration);
  printf("\n");
}
