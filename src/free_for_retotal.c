/***
 *** @file free_for_retotal.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_for_retotal(Ledger *ledger){
  int i, j;

  if(ledger == NULL)
    return;
  
  if(ledger->partition != NULL){
    for(i = 0; i < ledger->nbank; ++i){
      if(ledger->partition[i] != NULL){
        for(j = 0; j < ledger->npartition[i]; ++j)
          if(ledger->partition[i][j] != NULL)
            free(ledger->partition[i][j]);
        free(ledger->partition[i]);
      }
    }
    free(ledger->partition);
  }
  
  if(ledger->partition_totals != NULL){
    for(i = 0; i < ledger->nbank; ++i)
      if(ledger->partition_totals[i] != NULL)
        free(ledger->partition_totals[i]);
    free(ledger->partition_totals);
  }

  if(ledger->credit != NULL){
    for(i = 0; i < ledger->ncredit; ++i)
      if(ledger->credit[i] != NULL)
        free(ledger->credit[i]);
    free(ledger->credit); 
  }

  if(ledger->credit_totals != NULL){
    for(i = 0; i < ledger->ncredit; ++i)
      if(ledger->credit_totals[i] != NULL)
        free(ledger->credit_totals[i]);
    free(ledger->credit_totals); 
  }    

  if(ledger->bank != NULL){
    for(i = 0; i < ledger->nbank; ++i)
      if(ledger->bank[i] != NULL)
        free(ledger->bank[i]);
    free(ledger->bank);
  }

  if(ledger->bank_totals != NULL){
    for(i = 0; i < ledger->nbank; ++i)
      if(ledger->bank_totals[i] != NULL)
        free(ledger->bank_totals[i]);
    free(ledger->bank_totals);
  }

  if(ledger->npartition != NULL)
    free(ledger->npartition);
}
