/***
 *** @file unique.c
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

err_t unique(char **a, int n, char ***ret, int *nunique){
  int i, j, k;
  char **s;
  
  /* CHECK FOR NULL INPUT */
  
  if(a == NULL || n < 1)
    return LFAILURE;


  /* MAKE A SANITIZED LOCAL COPY OF INPUT AND CHECK IF MALLOC WORKED */
  
  s = malloc((n + 1) * sizeof(char*));
  if(s == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  s[0] = calloc(ENTRYSIZE, sizeof(char));
  if(s[0] == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  strcpy(s[0], NIL);
  for(j = 1; j < n + 1; ++j){
    str_strip(a[j - 1]);
    s[j] = calloc(ENTRYSIZE, sizeof(char));
    
    if(s[j] == NULL){
      fprintf(stderr, "Error: malloc failed.\n");
      
      for(k = 0; k < j; ++k)
        if(s[k] != NULL)
          free(s[k]);
      
      if(s != NULL)
        free(s);
      return LFAILURE;
    }
    
    if(a[j - 1] == NULL) {
      a[j - 1] = calloc(ENTRYSIZE, sizeof(char));
      
      if(a[j - 1] == NULL){
        fprintf(stderr, "Error: malloc failed.\n");
        for(k = 0; k < n + 1; ++k)
        if(s[k] != NULL)
          free(s[k]);
      
        if(s != NULL)
          free(s);
        return LFAILURE;
      }
      
      strcpy(s[j], NIL);
    } else {
      strcpy(s[j], a[j - 1]);
    }
  }


  /* SORT LOCAL COPY OF INPUT */

  qsort(s, n + 1, sizeof(char*), qcmp);

  /* FIND NUMBER OF UNIQUE STRINGS */

  i = 0;
  *nunique = 1;  
  for(j = 1; j < n + 1; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      ++(*nunique);
    }  

  /* ALLOCATE SPACE FOR NEW STRINGS AND CHECK IF MALLOC WORKED */
    
  *ret = malloc(*nunique * sizeof(char*));
  if(*ret == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  for(i = 0; i < *nunique; ++i){
    (*ret)[i] = calloc(ENTRYSIZE, sizeof(char));
    if(*ret == NULL){
      fprintf(stderr, "Error: malloc failed.\n");
      
      for(k = 0; k < i; ++k)
        if((*ret)[k] != NULL)
          free((*ret)[k]);
      free(*ret);    
      
      return LFAILURE;
    }
  }

  i = 0;
  k = 0;

  /* GET UNIQUE STRINGS AND SORT THEM */
 
  strcpy((*ret)[0], s[0]);
  for(j = 1; j < n + 1; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      strcpy((*ret)[k], s[j]);
      ++k;
    }  

  qsort(*ret, *nunique, sizeof(char*), qcmp);

  /* CLEAN UP AND RETURN */
    
  for(j = 0; j < n + 1; ++j)
    free(s[j]);
  free(s);  
  
  return LSUCCESS;
}

