/***
 *** @file contains_tabs.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/
 
#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

bool_t row_delim_char(char c){
  int i;
  char delims[] = ROW_SEPARATORS;
  for(i = 0; i < strlen(delims); ++i)
    if(c == delims[i])
      return LYES;
  return LNO;
}
