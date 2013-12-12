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

index_t col_delim_str(char *s){
  int i, n = strlen(s);
  for(i = 0; i < n; ++i)
    if(col_delim_char(s[i]))
      return i;
  return NO_INDEX;
}
