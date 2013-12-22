/**
 * @file        condense.c
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
 * @details Condenses a ledger object. Specifically, this function
 *          condenses all the cleared and unlocked transactions
 *          (rows) to make a smaller ledger with the same account 
 *          and partition totals. 
 */
err_t condense(Ledger *ledger){
  int row, bank, partition;
  
  /* check for null input */
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->nrows < 1)
    return LFAILURE;
    
  if(untotaled(ledger) == LYES)
    return LFAILURE;

  /* Subtract cleared and unlocked transactions from partition totals */
    
  for(row = 0; row < ledger->nrows; ++row){
    if(locked(ledger->entries[STATUS][row]) == LYES){ 
      bank = which(ledger->banks, ledger->entries[BANK][row], ledger->nbanks);
      partition = which(ledger->partitions[bank], ledger->entries[PARTITION][row], 
                        ledger->npartitions[bank]);  

      ledger->partition_totals[bank][partition] -= atof(ledger->entries[AMOUNT][row]);
    } else {
      strncpy(ledger->entries[AMOUNT][row], NIL, (ENTRYSIZE - 1) * sizeof(char)); 
    }
  }


  /* Make the "cleared" part of the ledger consist of either empty rows
     or the updated partition totals calculated above */
   
  for(row = 0; row < ledger->nrows; ++row){ 
    if(locked(ledger->entries[STATUS][row]) == LNO){
      bank = which(ledger->banks, ledger->entries[BANK][row], ledger->nbanks);
      partition = which(ledger->partitions[bank], ledger->entries[PARTITION][row], 
                        ledger->npartitions[bank]);
                        
      if(ledger->partition_totals[bank][partition] > EPS){
        snprintf(ledger->entries[AMOUNT][row], (ENTRYSIZE - 1) * sizeof(char),
                "%0.2f", ledger->partition_totals[bank][partition]);
        strncpy(ledger->entries[DESCRIPTION][row], "condensed", 
                (ENTRYSIZE - 1) * sizeof(char));
        ledger->partition_totals[bank][partition] = 0.0;
      }                  
    }
  }
  
  /* Remove the empty rows */
  
  if(trim_ledger(ledger) == LFAILURE)
    return LFAILURE;

  return LSUCCESS;
}
