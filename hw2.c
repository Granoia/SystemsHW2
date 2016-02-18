#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint8_t* make_buffer(int len)
{
  uint8_t* ret = malloc(8*len);
  for (int i=0; i < len; i++)
    {
      ret[i] = rand() % (1<<8 - 1);
    }
  return ret;
}



int main()
{
  srand(time(NULL));

  uint_t* buffer = make_buffer(20);
  for (int i=0; i < 20; i++)
    {
      printf("\n");
      printf("%d, ",buffer[i]);
    }
}
