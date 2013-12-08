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

void free_for_retotal(Ledger *ledger){
  int i, j;

  if(ledger == NULL)
    return;
  
  if(ledger->partitions != NULL){
    for(i = 0; i < ledger->nbanks; ++i){
      if(ledger->partitions[i] != NULL){
        for(j = 0; j < ledger->npartitions[i]; ++j)
          if(ledger->partitions[i][j] != NULL)
            free(ledger->partitions[i][j]);
        free(ledger->partitions[i]);
      }
    }
    free(ledger->partitions);
  }
  
  if(ledger->partition_totals != NULL){
    for(i = 0; i < ledger->nbanks; ++i)
      if(ledger->partition_totals[i] != NULL)
        free(ledger->partition_totals[i]);
    free(ledger->partition_totals);
  }

  if(ledger->credits != NULL){
    for(i = 0; i < ledger->ncredits; ++i)
      if(ledger->credits[i] != NULL)
        free(ledger->credits[i]);
    free(ledger->credits); 
  }

  if(ledger->credit_totals != NULL){
    for(i = 0; i < ledger->ncredits; ++i)
      if(ledger->credit_totals[i] != NULL)
        free(ledger->credit_totals[i]);
    free(ledger->credit_totals); 
  }    

  if(ledger->banks != NULL){
    for(i = 0; i < ledger->nbanks; ++i)
      if(ledger->banks[i] != NULL)
        free(ledger->banks[i]);
    free(ledger->banks);
  }

  if(ledger->bank_totals != NULL){
    for(i = 0; i < ledger->nbanks; ++i)
      if(ledger->bank_totals[i] != NULL)
        free(ledger->bank_totals[i]);
    free(ledger->bank_totals);
  }

  if(ledger->npartitions != NULL)
    free(ledger->npartitions);
}
