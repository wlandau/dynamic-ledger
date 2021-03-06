/**
 * @file        unique.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Finds all the unique elements in an array of character strings.
 *          You can treat "a" and "n" as the arguments, and ret and nunique
 *          as the return values (passed by reference). ret and nunique should
 *          be unallocated and uninitialized when unique is called. IMPORTANT
 *          NOTE: unique adds a blank character string to the list of unique
 *          character strings if one is not already present. This is so that
 *          every ledger automatically has an unnamed bank account, an unnamed
 *          credit account, and an unnamed bank partition for every bank account.
 */
err_t unique(char **a, int n, char ***ret, int *nunique){
  int i, j, k;
  char **s;
  
  /* Check for null input */
  
  if(a == NULL || n < 1)
    return LFAILURE;

  /* Make a sanitized local copy of input and check if calloc worked */
  
  s = calloc((n + 1), sizeof(char*));
  if(s == NULL){
    fprintf(stderr, "Error: calloc failed.\n");
    return LFAILURE;
  }
  
  s[0] = calloc(ENTRYSIZE, sizeof(char));
  if(s[0] == NULL){
    fprintf(stderr, "Error: calloc failed.\n");
    return LFAILURE;
  }
  
  strncpy(s[0], NIL, (ENTRYSIZE - 1) * sizeof(char));
  for(j = 1; j < n + 1; ++j){
    str_strip(a[j - 1]);
    s[j] = calloc(ENTRYSIZE, sizeof(char));
    
    if(s[j] == NULL){
      fprintf(stderr, "Error: calloc failed.\n");
      
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
        fprintf(stderr, "Error: calloc failed.\n");
        for(k = 0; k < n + 1; ++k)
        if(s[k] != NULL)
          free(s[k]);
      
        if(s != NULL)
          free(s);
        return LFAILURE;
      }
      
      strncpy(s[j], NIL, (ENTRYSIZE - 1) * sizeof(char));
    } else {
      strncpy(s[j], a[j - 1], (ENTRYSIZE - 1) * sizeof(char));
    }
  }

  /* Sort a local copy of the input array of strings */

  qsort(s, n + 1, sizeof(char*), qcmp);

  /* FIND NUMBER OF UNIQUE STRINGS */

  i = 0;
  *nunique = 1;  
  for(j = 1; j < n + 1; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      ++(*nunique);
    }  

  /* Allocate space for the array of unique strings and check if calloc worked */
    
  *ret = calloc(*nunique, sizeof(char*));
  if(*ret == NULL){
    fprintf(stderr, "Error: calloc failed.\n");
    return LFAILURE;
  }
  
  for(i = 0; i < *nunique; ++i){
    (*ret)[i] = calloc(ENTRYSIZE, sizeof(char));
    if(*ret == NULL){
      fprintf(stderr, "Error: calloc failed.\n");
      
      for(k = 0; k < i; ++k)
        if((*ret)[k] != NULL)
          free((*ret)[k]);
      free(*ret);    
      
      return LFAILURE;
    }
  }

  i = 0;
  k = 0;

  /* Get unique strings and sort them */
 
  strncpy((*ret)[0], s[0], (ENTRYSIZE - 1) * sizeof(char));
  for(j = 1; j < n + 1; ++j)
    if(!str_equal(s[i], s[j])){
      i = j;
      strncpy((*ret)[k], s[j], (ENTRYSIZE - 1) * sizeof(char));
      ++k;
    }  

  qsort(*ret, *nunique, sizeof(char*), qcmp);

  /* Clean up and return */
    
  for(j = 0; j < n + 1; ++j)
    free(s[j]);
  free(s);  
  
  return LSUCCESS;
}

