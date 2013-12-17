/***
 *** @file condense.c
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

err_t condense(Ledger *ledger){
  int row, bank, partition;
  
  if(ledger == NULL)
    return LFAILURE;
    
  if(untotaled(ledger) == LYES)
    return LFAILURE;

  /* SUBTRACT TRANSACTIONS WITH NONTRIVIAL STATUSES FROM BANK TOTALS, ETC. */
    
  for(row = 0; row < ledger->nrows; ++row){
    if(locked(ledger->entries[STATUS][row]) == LYES){ 
      bank = which(ledger->banks, ledger->entries[BANK][row], ledger->nbanks);
      partition = which(ledger->partitions[bank], ledger->entries[PARTITION][row], 
                        ledger->npartitions[bank]);  

      ledger->partition_totals[bank][partition] -= atof(ledger->entries[AMOUNT][row]);
    } else {
      strcpy(ledger->entries[AMOUNT][row], NIL); 
    }
  }

  /* MAKE THE NONZERO "TRANSACTIONS" OF THE LEDGER CONSIST ONLY OF
   * TRANSACTIONS WITH NONTRIVIAL STATUS AND PARTITION TOTALS */
   
  for(row = 0; row < ledger->nrows; ++row){ 
    if(locked(ledger->entries[STATUS][row]) == LNO){
      bank = which(ledger->banks, ledger->entries[BANK][row], ledger->nbanks);
      partition = which(ledger->partitions[bank], ledger->entries[PARTITION][row], 
                        ledger->npartitions[bank]);
                        
      if(ledger->partition_totals[bank][partition] > EPS){
        sprintf(ledger->entries[AMOUNT][row], "%0.2f", 
                ledger->partition_totals[bank][partition]);
        strcpy(ledger->entries[DESCRIPTION][row], "condensed");
        ledger->partition_totals[bank][partition] = 0.0;
      }                  
    }
  }
  
  /* REMOVE THE EMPTY ROWS */
  
  if(trim_ledger(ledger) == LFAILURE)
    return LFAILURE;

  return LSUCCESS;
}
