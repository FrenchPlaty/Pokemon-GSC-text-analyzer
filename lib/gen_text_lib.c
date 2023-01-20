#include <stdio.h>

#include "gen_text_lib.h"


void print(char **char_array){
  for(int i = 0 ; i < ARRAY_SIZE*ARRAY_SIZE ; ++i)
  {
    printf("%s\n",char_array[i]);
  }
}
