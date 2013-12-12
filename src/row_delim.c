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

int row_delim(char *s){
  char delims[] = ROW_SEPARATORS;
  int i, j, n = strlen(s), ndelims = strlen(delims);
  for(i = 0; i < n; ++i)
    for(j = 0; j < ndelims; ++j)
      if(s[i] == delims[j])
        return i;
  return NONE_FOUND;
}
