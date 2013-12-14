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

index_t which(char **s, char *find, int n){
  int low = 0, high = n - 1, mid, c;
  
  if(s == NULL || find == NULL || n < 1)
    return NO_INDEX;
    
  while(abs(high - low) > 1){
    mid = (high + low)/2;
    c = strcmp(s[mid], find);
    if(c > 0)
      high = mid;
    else if(c < 0)
      low = mid;
    else
      low = high = mid;
  }  
 
  if(!strcmp(s[low], find))
    return low;
  else if(!strcmp(s[high], find))
    return high;
  else
    return NO_INDEX;
}
