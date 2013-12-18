/***
 *** @file alloc_entries.c
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

err_t alloc_entries(Ledger *ledger){
  int i, j, nrows;
  err_t ret;
  
  /* check for null input */
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->nrows < 1)
    return LFAILURE;

  /* clear previous entries */
  
  nrows = ledger->nrows;
  free_entries(ledger);
  ledger->nrows = nrows;

  /* allocate entries */
  
  ledger->entries = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->entries[i] = malloc(ledger->nrows * sizeof(char*));
    for(j = 0; j < ledger->nrows; ++j)
      ledger->entries[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }
  
  /* test if malloc worked */
  
  ret = LSUCCESS;
  if(ledger->entries == NULL){
    fprintf(stderr, "Error: malloc failed\n");
    ret = LFAILURE;
  } else {
    for(i = 0; i < NFIELDS; ++i){
      if(ledger->entries[i] == NULL){
        fprintf(stderr, "Error: malloc failed\n");
        ret = LFAILURE;
        break;
      }
      for(j = 0; j < ledger->nrows; ++j)
        if(ledger->entries[i][j] == NULL){
          fprintf(stderr,"Error: malloc failed\n");
          ret = LFAILURE;
          break;
        }
    }
  }
  
  return ret;
}
