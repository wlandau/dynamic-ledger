/**
 * @file        untotaled.c
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
 * @details  Checks if account totals have been calculated for a Ledger object.
 *           If not calculated, pointers to these totals should have already
 *           been initialized to NULL by new_ledger. Returns LYES if totals have
 *           been calculated and LNO otherwise.
 */ 
bool_t untotaled(Ledger *ledger){
  if(ledger == NULL)
    return LYES;
    
  if(ledger->banks == NULL || ledger->credits == NULL || ledger->partitions == NULL ||
     !ledger->nbanks || !ledger->ncredits || ledger->npartitions == NULL)  
    return LYES;
  
  if(ledger->bank_totals == NULL || ledger->credit_totals == NULL || 
     ledger->partition_totals == NULL)
    return LYES;
    
  return LNO;
}
