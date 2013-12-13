/***
 *** @file get_totals.c
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

err_t get_totals(Ledger *ledger){
  int i, j, k, status, bank, credit, partition;
  double amount;

  if(alloc_totals(ledger) == LFAILURE)
    return LFAILURE;


/*

  for(i = 0; i < ledger->nrows; ++i){
    
    status = which_status_bank(ledger->entries[STATUS][i]);
    amount = atof(ledger->entries[AMOUNT][i]);

    k = -1;
    if(str_equal(status, CREDIT_NOT_THERE_YET)){
      k = 0;
    } else if(str_equal(status, CREDIT_PENDING)){
      k = 1;
    } else if(str_equal(status, CREDIT_CLEARED)){
      k = 2;
    } 

    if(k != -1)
      for(j = 0; j < ledger->ncredits; ++j) 
        if(str_equal(ledger->entries[CREDIT][i], ledger->credits[j])){
          ledger->credit_totals[j][k] += amount;
          break;
        }
      
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) || 
       str_equal(status, NOT_THERE_YET)){
      k = 0;
    } else if(str_equal(status, PENDING)){
      k = 1;
    } else {
      k = 2;
    }
    
    for(j = 0; j < ledger->nbanks; ++j){
      if(str_equal(ledger->entries[BANK][i], ledger->banks[j])){
        ledger->bank_totals[j][k] += amount;

        for(k = 0; k < ledger->npartitions[j]; ++k){
          if(str_equal(ledger->entries[PARTITION][i], ledger->partitions[j][k])){
            ledger->partition_totals[j][k] += amount;
            break;
          }
        } 

        break;
      }
    }
  }
  
  for(j = 0; j < ledger->ncredits; ++j)
    for(k = 0; k < 3; ++k)
      ledger->credit_totals[j][I_OVERALL] += ledger->credit_totals[j][k];

  for(j = 0; j < ledger->nbanks; ++j)
    for(k = 0; k < 3; ++k){
      ledger->bank_totals[j][I_OVERALL] += ledger->bank_totals[j][k];
    }  
    */
  return LSUCCESS;
}
