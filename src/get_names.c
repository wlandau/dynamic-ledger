/**
 * @file get_names.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Gets the account names of a ledger object.
 *          Specifically, fills the banks, credits, and partitions
 *          member arrays of the Ledger object.
 */
err_t get_names(Ledger *ledger){
  int i, j;
  err_t ret;
  char **s;
  
  /* Check for null input */
  
  if(ledger == NULL) 
    return LFAILURE;
    
  if(ledger->nrows < 1)
    return LFAILURE;

  if(unique(ledger->entries[CREDIT], 
          ledger->nrows, 
          &ledger->credits, 
          &ledger->ncredits) == LFAILURE){

    return LFAILURE;
  }

  if(unique(ledger->entries[BANK], 
            ledger->nrows, 
            &ledger->banks, 
            &ledger->nbanks) == LFAILURE){

    return LFAILURE;  
  }
  
  /* Allocate arrays for partition names */
  
  ledger->npartitions = calloc(ledger->nbanks, sizeof(int*));
  ledger->partitions = malloc(ledger->nbanks * sizeof(char***));

  /* Check if malloc worked */

  if(ledger->partitions == NULL || ledger->npartitions == NULL){
    fprintf(stderr, "Error: malloc failed\n");
    return LFAILURE;
  }

  /* Allocate array for sorted partition names */
  
  s = malloc(ledger->nrows * sizeof(char*));
  for(i = 0; i < ledger->nrows; ++i)
    s[i] = calloc(ENTRYSIZE, sizeof(char));

  /* Check if malloc worked */

  ret = LSUCCESS;
  if(s == NULL){
    fprintf(stderr, "Error: malloc failed\n");
    ret = LFAILURE;
  } else {
    for(i = 0; i < ledger->nrows; ++i)
      if(s[i] == NULL){
        fprintf(stderr, "Error: malloc failed\n");
        ret = LFAILURE;
      }
  }
  
  if(ret == LFAILURE){
    if(s != NULL){
      for(i = 0; i < ledger->nrows; ++i)
        if(s[i] != NULL)
          free(s[i]);
      free(s);
    }
    return LFAILURE;
  }
  
  /* Get partition names */
        
  for(i = 0; i < ledger->nbanks; ++i){
    for(j = 0; j < ledger->nrows; ++j){    
      if(str_equal(ledger->banks[i], ledger->entries[BANK][j]))     
        strcpy(s[j], ledger->entries[PARTITION][j]);
      else
        strcpy(s[j], NIL);
    }
     
    if(unique(s, ledger->nrows, 
              &(ledger->partitions[i]), 
              &(ledger->npartitions[i])) == LFAILURE){

      for(i = 0; i < ledger->nrows; ++i)
        free(s[i]);
      free(s);
              
      return LFAILURE;
    }
  }
  
  /* Clean up and return */
  
  for(i = 0; i < ledger->nrows; ++i)
    free(s[i]);
  free(s);
  
  return LSUCCESS;
}
