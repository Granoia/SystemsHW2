#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
/*contains the function shuffle(<list>,<length>) which shuffles the entries of a list. */

uint8_t* make_buffer(int len){
  uint8_t* ls = malloc(8*len);
  for(int i=0;i<len;i++){
    ls[i] = i;
  }
  return ls;
}


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


int main(int argc, char** argv){
  if (argc != 2){
    printf("%s <length>\n", argv[0]);
    return -1;
  }
  srand(time(NULL));
  const int length = atoi(argv[1]);
  printf("MAIN length is: %i\n", length);
  uint8_t* ls = make_buffer(length);
  for(int i=0;i<length;i++){
    printf("%i\n",ls[i]);
  }
  shuffle(ls, length);
  for(int i=0;i<length;i++){
    printf("%i\n",ls[i]);
      }
  free(ls);
  return 0;
}
