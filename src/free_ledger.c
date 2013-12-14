/***
 *** @file free_ledger.c
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

void free_ledger(Ledger **ledger){
  int i, j;

  if(ledger == NULL)
    return;
    
  if(*ledger == NULL)
    return;

  if((*ledger)->filename != NULL){
    free((*ledger)->filename);
    (*ledger)->filename = NULL;
  }
  
  if((*ledger)->entries != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if((*ledger)->entries[i] != NULL){
        for(j = 0; j < (*ledger)->nrows; ++j)
          if((*ledger)->entries[i][j] != NULL){
            free((*ledger)->entries[i][j]);
            (*ledger)->entries[i][j] = NULL;
          }
        free((*ledger)->entries[i]);
        (*ledger)->entries[i] = NULL;
      }
    }
    free((*ledger)->entries);
    (*ledger)->entries = NULL;
  }
  
  free_for_retotal(*ledger);
  free(*ledger);
  *ledger = NULL;
}
