#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#include "text_decoder.h"
#include "gen_text_lib.h"

void setup_char_array(char *char_array[])
{
  FILE *file      = fopen("src/array_US","r");
  int   buffer    = 0, //This will be used to read characters individually with getc
        increment = 0,
        array_inc = 0, //Same shit as increment but for array position (KEEP IN MIND THIS IS NOT A 2D ARRAY)
        flag      = 0; //Has to be used because whitespaces are valid characters in the encoding table for some fucking reason
  if(file == NULL)
  {
    fprintf(stderr,"An error has occured when opening the encoding array file.\n");
    exit(FILE_NOT_FOUND_ERROR);
  }

  char_array[0] = malloc(MAX_STRING_SIZE);
  while(!feof(file))
  {
    buffer = getc(file);
    switch((char)buffer)
    {
      case ' ': case '\n':
        if(flag){
          char_array[array_inc][increment] = (char)buffer;
          increment++;
          flag=0;
        }
        else
        {
          increment = 0;
          array_inc++;
          char_array[array_inc] = malloc(MAX_STRING_SIZE);
          flag=1;
        }
        break;
      
      default:
        char_array[array_inc][increment] = (char)buffer;
        increment++;
        flag=0;
        break;
    }
  }
  close(file);
}


void read_and_convert(FILE *file, char **char_array, int b_offset, int e_offset)
{
  int buffer = 0x00;
  
  if(fseek(file, b_offset, SEEK_SET) == -1){
    fprintf(stderr,"An error has occured while setting the cursor.\n");
    exit(errno);
  }
  while(ftell(file) != e_offset )
  {
    buffer = getc(file);
    //use 0xF0 and 0x0F masks
    printf("%s",char_array[((char)buffer & 0xF0)+((char)buffer & 0x0F)]); // just realized this is useless
  }
  printf("\n");
}

