#ifndef TEXT_DECODER_H
#define TEXT_DECODER_H
//General functions for decoding the text will go here
//this includes
/*
 * Setting up the array (using the appropriate decoding file)
 * printing the desired segment of the ROM or the entire ROM if needed
 * TODO: write more if needed or if inspiration comes during drunken nights
 */

void setup_char_array(char *char_array[]);
void read_and_convert(FILE *file, char **char_array, int b_offset, int e_offset);

#endif
