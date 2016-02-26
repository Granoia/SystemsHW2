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

//makes a buffer formed of blocks of integers from 0 to 2^8-1
uint8_t* make_blockbuffer(int len){
  if(len < (1 << 8)){
    printf("Size must be 2^8 or higher\n");
    exit(-1);
  }

  uint8_t* ret = malloc(8*len);
  uint8_t block_counter = 0;
  for (int i=0; i < len; i++){
    ret[i] = block_counter;
    if (block_counter < 255){
      block_counter ++;
    }
    else{
      block_counter = 0;
    }
  }
  return ret;
}

//This algorithm looks up bytes by picking a random 2^8 sized block in the buffer, going there and then adding the value of the previously picked byte to the index, starting with 0

void random_access_model2(uint8_t* buffer, int size, uint8_t* trash){
  uint8_t add_to_index = 0;
  int num_blocks = size/(1<<8);
  int pick_a_block = rand() % (num_blocks);
  uint8_t lookup = 0;
  const int TWOtotheEIGHT = 1 << 8;
  for (int i=0; i<size; i++){
      lookup = buffer[add_to_index + (pick_a_block * TWOtotheEIGHT)];
      trash[i] = lookup;
      add_to_index = lookup;
      pick_a_block = rand() % (num_blocks);
    }
}


void dummy_random_access(int size){
  int num_blocks = size/(1<<8);
  int pick_a_block = rand() % (num_blocks);
  uint8_t add_to_index = 0;
  int dummy = 0;
  const int TWOtotheEIGHT = 1 << 8;

  for (int i=0; i<size; i++){
    dummy = add_to_index + (pick_a_block * TWOtotheEIGHT);
    pick_a_block = rand() % (num_blocks);
    add_to_index = dummy % TWOtotheEIGHT;
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
  const uint64_t size = 1 << atoi(argv[1]);
  const uint64_t iters = 1 << atoi(argv[2]);
  const int BILLION = 1000000000;
  const char outputFilename[] = "temp.txt";
 
  //Initialization
  srand(time(NULL));
  struct timespec begin;
  struct timespec end;
  struct timespec dummyend;
  uint8_t* buffer = make_blockbuffer(size);
  shuffle(buffer, size);
  uint8_t* trash = malloc(8*size);
  printf("Buffer loaded.\n");

  //Timing the loop
  clock_gettime(CLOCK_MONOTONIC, &begin);
  for (int i=0; i < iters; i++) 
  {
    random_access_model2(buffer, size,trash);
  }
  clock_gettime(CLOCK_MONOTONIC, &end);
  for (int i=0; i < iters; i++){
    dummy_random_access(size);
  }
  clock_gettime(CLOCK_MONOTONIC, &dummyend);
  free(buffer);
  free(trash);
  //Output the time
  double duration = BILLION*(end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec);
  double dummyduration = BILLION*(dummyend.tv_sec - end.tv_sec) + (dummyend.tv_nsec - end.tv_nsec);
  double adjusted = duration - dummyduration;
  duration /= iters*size;
  dummyduration /= iters*size;
  adjusted /= iters*size;
  printf("Duration: %fns",duration);
  printf("\n");
  printf("Dummy Duration: %fns",dummyduration);
  printf("\n");
  printf("Adjusted Duration: %fns",adjusted);
  printf("\n");

  //Write time to a file
  FILE* fileout = fopen(outputFilename, "a");
  fprintf(fileout, "%s,%f,%f,%s\n",argv[1], duration, adjusted, argv[2]);
  fclose(fileout);

  return 0;
}
