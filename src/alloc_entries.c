/***
 *** @file alloc_text_content.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t alloc_entries(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->nrows < 1)
    return LFAILURE;

  if(ledger->entries != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(ledger->entries[i] != NULL){
        for(j = 0; j < ledger->nrows; ++j)
          if(ledger->entries[i][j] != NULL)
            free(ledger->entries[i][j]);
        free(ledger->entries[i]);
      }
    }
    free(ledger->entries);
  }

  ledger->entries = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->entries[i] = malloc(ledger->nrows * sizeof(char*));
    for(j = 0; j < ledger->nrows; ++j)
      ledger->entries[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }
  
  return LSUCCESS;
}
