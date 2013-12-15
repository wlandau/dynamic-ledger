/***
 *** @file free_ledger.c
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

err_t free_ledger(Ledger **ledger){
  int i, j;
  err_t ret;

  if(ledger == NULL)
    return LFAILURE;
    
  if(*ledger == NULL)
    return LFAILURE;

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
  
  ret = free_for_retotal(*ledger);
  free(*ledger);
  *ledger = NULL;
  
  return ret;
}
