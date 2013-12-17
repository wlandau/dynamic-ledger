/***
 *** @file free_entries.c
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

err_t free_entries(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->entries != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(ledger->entries[i] != NULL){
        for(j = 0; j < ledger->nrows; ++j)
          if(ledger->entries[i][j] != NULL){
            free(ledger->entries[i][j]);
            ledger->entries[i][j] = NULL;
          }
        free(ledger->entries[i]);
        ledger->entries[i] = NULL;
      }
    }
    free(ledger->entries);
    ledger->entries = NULL;
  }
  
  return LSUCCESS;
}
