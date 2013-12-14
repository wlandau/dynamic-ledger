/***
 *** @file free_for_retotal.c
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

err_t free_for_retotal(Ledger *ledger){
  int i, j;

  if(ledger == NULL)
    return LFAILURE;
  
  if(ledger->partitions != NULL){
    for(i = 0; i < ledger->nbanks; ++i){
      if(ledger->partitions[i] != NULL){
        for(j = 0; j < ledger->npartitions[i]; ++j)
          if(ledger->partitions[i][j] != NULL){
            free(ledger->partitions[i][j]);
            ledger->partitions[i][j] = NULL;
          }
        free(ledger->partitions[i]);
        ledger->partitions[i] = NULL;
      }
    }
    free(ledger->partitions);
    ledger->partitions = NULL;
  }
  
  if(ledger->partition_totals != NULL){
    for(i = 0; i < ledger->nbanks; ++i)
      if(ledger->partition_totals[i] != NULL){
        free(ledger->partition_totals[i]);
        ledger->partition_totals[i] = NULL;
      }
    free(ledger->partition_totals);
    ledger->partition_totals = NULL;
  }

  if(ledger->credits != NULL){
    for(i = 0; i < ledger->ncredits; ++i)
      if(ledger->credits[i] != NULL){
        free(ledger->credits[i]);
        ledger->credits[i] = NULL;
      }
    free(ledger->credits);
    ledger->credits = NULL; 
  }

  if(ledger->credit_totals != NULL){
    for(i = 0; i < ledger->ncredits; ++i)
      if(ledger->credit_totals[i] != NULL){
        free(ledger->credit_totals[i]);
        ledger->credit_totals[i] = NULL;
      }
    free(ledger->credit_totals); 
    ledger->credit_totals = NULL;
  }    

  if(ledger->banks != NULL){
    for(i = 0; i < ledger->nbanks; ++i)
      if(ledger->banks[i] != NULL){
        free(ledger->banks[i]);
        ledger->banks[i] = NULL;
      }
    free(ledger->banks);
    ledger->banks = NULL;
  }

  if(ledger->bank_totals != NULL){
    for(i = 0; i < ledger->nbanks; ++i)
      if(ledger->bank_totals[i] != NULL){
        free(ledger->bank_totals[i]);
        ledger->bank_totals[i] = NULL;
      }
    free(ledger->bank_totals);
    ledger->bank_totals = NULL;
  }

  if(ledger->npartitions != NULL){
    free(ledger->npartitions);
    ledger->npartitions = NULL;
  }

  return LSUCCESS;
}
