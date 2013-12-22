/**
 * @file        retotal.c
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
 * @details Call free_for_retotal, get_names, and get_totals to
 *          reflect any recent changes to ledger->entries.
 */

err_t retotal(Ledger *ledger){

  /* Check for NULL input */

  if(ledger == NULL)
    return LFAILURE;

  if(ledger->nrows < 1 || ledger->entries == NULL)
    return LFAILURE;

  /* Update the data in the ledger to reflect recent changes. */

  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
      
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
        
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
      
  return LSUCCESS;
}
