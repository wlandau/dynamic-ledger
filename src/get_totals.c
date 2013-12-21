/**
 * @file        get_totals.c
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
 * @details Compute numerical summaries on a Ledger object.
 *          These summaries are stored in bank_totals, credit_totals,
 *          and partition_totals.
 */
err_t get_totals(Ledger *ledger){
  int row, bank, credit, partition, bank_total, credit_total;
  double amount;

  if(ledger == NULL)
    return LFAILURE;  

  if(ledger->nrows < 1)
    return LFAILURE;
  
  if(alloc_totals(ledger) == LFAILURE)
    return LFAILURE;

  for(row = 0; row < ledger->nrows; ++row){
    amount = atof(ledger->entries[AMOUNT][row]);
    bank_total = which_bank_total(ledger->entries[STATUS][row]);
    credit_total = which_credit_total(ledger->entries[STATUS][row]);
    credit = which(ledger->credits, ledger->entries[CREDIT][row], ledger->ncredits);  
    bank = which(ledger->banks, ledger->entries[BANK][row], ledger->nbanks);
    partition = which(ledger->partitions[bank], ledger->entries[PARTITION][row], 
                      ledger->npartitions[bank]);  
      
    if(credit_total != NO_INDEX)
      ledger->credit_totals[credit][credit_total] += amount;
      
    if(bank_total != NO_INDEX)
      ledger->bank_totals[bank][bank_total] += amount;
      
    if(partition != NO_INDEX)
      ledger->partition_totals[bank][partition] += amount;
  }

  for(credit = 0; credit < ledger->ncredits; ++credit){
  
    ledger->credit_totals[credit][I_PENDING_BAL] = 
        ledger->credit_totals[credit][I_PENDING]
      + ledger->credit_totals[credit][I_CLEARED];
  
    ledger->credit_totals[credit][I_OVERALL_BAL] = 
        ledger->credit_totals[credit][I_NOT_THERE_YET]
      + ledger->credit_totals[credit][I_PENDING_BAL];
  }
  
  for(bank = 0; bank < ledger->nbanks; ++bank){
    ledger->bank_totals[bank][I_PENDING_BAL] = 
        ledger->bank_totals[bank][I_PENDING]
      + ledger->bank_totals[bank][I_CLEARED];
  
    ledger->bank_totals[bank][I_OVERALL_BAL] = 
        ledger->bank_totals[bank][I_NOT_THERE_YET]
      + ledger->bank_totals[bank][I_PENDING_BAL];
  }

  return LSUCCESS;
}
