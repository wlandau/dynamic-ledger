/**
 * @file row_delim_char.c
 * @author Will Landau (http://www.will-landau.com/)
 */
 
#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Tests if the given character is one of the legal
 *          row separators given in the character string
 *          macro, ROW_SEPARATORS.
 */
bool_t row_delim_char(char c){
  int i;
  char delims[] = ROW_SEPARATORS;
  for(i = 0; i < strlen(delims); ++i)
    if(c == delims[i])
      return LYES;
  return LNO;
}
