/**
 * @file        free_for_retotal.c
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
 * @details  Frees the account names and numerical summaries of a Ledger object.
 *           bank_totals, credit_totals, partition_totals, banks, credits, etc.
 *           are freed. This is so that the numerical summaries and account names
 *           can be recomputed after a change to the Ledger object.
 */
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

  ledger->nbanks = 0;
  ledger->ncredits = 0;
  
  return LSUCCESS;
}
