/***
 *** @file unique.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t unique(char **a, int n, char ***ret, int *nunique){
  int i, j, k;
  char **s;
  
  if(a == NULL || n < 1)
    return LFAILURE;
  
  s = malloc((n + 1) * sizeof(char*));
  s[0] = calloc(ENTRYSIZE, sizeof(char));
  strcpy(s[0], NIL);
  for(j = 1; j < n + 1; ++j){
    str_strip(a[j - 1]);
    s[j] = calloc(ENTRYSIZE, sizeof(char));
    
    if(a[j - 1] == NULL) {
      a[j - 1] = calloc(ENTRYSIZE, sizeof(char));
      strcpy(s[j], NIL);
    } else {
      strcpy(s[j], a[j - 1]);
    }
  }

  qsort(s, n + 1, sizeof(char*), qcmp);

  i = 0;
  *nunique = 1;  
  for(j = 1; j < n + 1; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      ++(*nunique);
    }  
    
  *ret = malloc(*nunique * sizeof(char*));
  for(i = 0; i < *nunique; ++i)
    (*ret)[i] = calloc(ENTRYSIZE, sizeof(char));

  i = 0;
  k = 0;
 
  strcpy((*ret)[0], s[0]);
  for(j = 1; j < n + 1; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      strcpy((*ret)[k], s[j]);
      ++k;
    }  

  qsort(*ret, *nunique, sizeof(char*), qcmp);
    
  for(j = 0; j < n + 1; ++j)
    free(s[j]);
  free(s);  
  
  return LSUCCESS;
}

