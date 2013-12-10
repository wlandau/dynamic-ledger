/***
 *** @file unique.c
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

void unique(char **a, int n, char ***ret, int *nunique){
  int i, j, k;
  char **s;
  
  if(a == NULL || n < 1)
    return;
  
  s = malloc(n * sizeof(char*));
  for(j = 0; j < n; ++j){
    s[j] = malloc(ENTRYSIZE * sizeof(char));
    
    if(a[j] == NULL)
      strcpy(s[j], NIL);
    else
      strcpy(s[j], a[j]);
  }

  qsort(s, n, sizeof(char*), qcmp);

  i = 0;
  *nunique = 1;  
  for(j = 0; j < n; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      ++(*nunique);
    }  
    
  *ret = malloc(*nunique * sizeof(char*));
  for(i = 0; i < *nunique; ++i)
    (*ret)[i] = calloc(ENTRYSIZE, sizeof(char));

  i = 0;
  k = 0;
 
  for(j = 1; j < n; ++j)
    if(!str_equal(s[i], s[j]) && !str_equal(NIL, s[j])){
      i = j;
      strcpy((*ret)[k], s[j]);
      ++k;
    }  
    
  for(j = 0; j < n; ++j)
    free(s[j]);
  free(s);  
}

