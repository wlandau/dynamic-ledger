/***
 *** @file col_delim_char.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/
 
#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

bool_t col_delim_char(char c){
  int i;
  char delims[] = COLUMN_SEPARATORS;
  for(i = 0; i < strlen(delims); ++i)
    if(c == delims[i])
      return LYES;
  return LNO;
}
