/***
 *** @file which.c
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

int which(char **s, const char *find, int n){
  int i;
  
  if(s == NULL || n < 1)
    return -1;
    
  for(i = 0; i < n; ++i)
    if(str_equal(s[i], find))
      return i;
  
  return -1;
}
