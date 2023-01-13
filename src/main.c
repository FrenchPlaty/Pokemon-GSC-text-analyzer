#include <stdio.h>
#include <stdlib.h>

#include <errno.h>

#define ARGUMENT_ERROR 205
#define FILE_NOT_FOUND_ERROR 404

#define ARRAY_SIZE 0x10
#define MAX_STRING_SIZE 30

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

void print(char **char_array){
  for(int i = 0 ; i < ARRAY_SIZE*ARRAY_SIZE ; ++i)
  {
    printf("%s\n",char_array[i]);
  }
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
    printf("%s",char_array[((char)buffer & 0xF0)+((char)buffer & 0x0F)]);
  }
  printf("\n");
}

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
