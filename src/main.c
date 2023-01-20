#include <stdio.h>
#include <stdlib.h>

#include "../lib/text_decoder.h"
#include "../lib/gen_text_lib.h"

int main(int argc, char **argv)
{
  if(argc != 4)
  {
    fprintf(stderr, "Argument error : File path - Beginning offset - Ending offset");
    exit(ARGUMENT_ERROR);
  }

  char *char_array[ARRAY_SIZE*ARRAY_SIZE]; //Used for encoding
  FILE *file = fopen(argv[1],"r");
  setup_char_array(char_array);
  
  if(file == NULL)
  {
    fprintf(stderr,"The input file could not be opened.");
    exit(FILE_NOT_FOUND_ERROR);
  }
  //print(char_array);
  printf("%ld %ld",strtol(argv[2],NULL,0),strtol(argv[3],NULL,0));
  read_and_convert(file, char_array, strtol(argv[2],NULL,0), strtol(argv[3],NULL,0));

  return 0;
}
