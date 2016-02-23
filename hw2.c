#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define BILLION 1000000000

FILE *fileout;
const char outputFilename[] = "temp.txt";

uint8_t* make_buffer(int len)
{
  uint8_t* ret = malloc(8*len);
  for (int i=0; i < len; i++)
    {
      ret[i] = rand() % len;
    }
  return ret;
}


void access_at_random(uint8_t* buffer, int size,uint8_t* trash)
{
  for (int i=0; i < size; i++)
    {
      trash[i] = buffer[i];
    }
}

//Shuffles a list of ints
void shuffle(uint8_t* ls, int length){
  printf("Length of list is: %d\n", length);
  for(int i=0; i<length; i++){
    int j = rand() % (length-i);
    uint8_t a = ls[i];
    uint8_t b = ls[i+j];
    ls[i] = b;
    ls[i+j] = a;
  }
  return;
}

int main(int argc, char** argv)
{
  printf("%lu\n",sizeof(int));
  if (argc != 3) 
  {
    printf("%s <2^size> <2^iters>\n",argv[0]);
    return 0;
  }

  const int size = 1 << atoi(argv[1]);
  const int iters = 1 << atoi(argv[2]);
 
  //Initialization
  srand(time(NULL));
  struct timespec begin;
  struct timespec end;
  uint8_t* buffer = make_buffer(size);
  uint8_t* trash = malloc(8*size);
  printf("Buffer loaded.\n");

  //Timing the loop
  clock_gettime(CLOCK_MONOTONIC, &begin);
  for (int i=0; i < iters; i++) 
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

  //Write time to a file
  fileout = fopen(outputFilename, "a");
  fprintf(fileout, "%f\n", duration);
  fclose(fileout);

  return 0;
}
