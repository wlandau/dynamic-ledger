/**
 * @file        rename_credit.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Safely renames a credit account and
 *          updates the other data in the Ledger
 *          object to reflect  the change. 
 */
err_t rename_credit(Ledger *ledger, char *from, char *to){
  int i;

  /* Check for NULL input */

  if(ledger == NULL)
    return LFAILURE;

  /* Rename the credit account */

  for(i = 0; i < ledger->nrows; ++i)
    if(str_equal(ledger->entries[CREDIT][i], from))
      strcpy(ledger->entries[CREDIT][i], to);

  /* Update the rest of the data in the Ledger object to reflect the change */
      
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
  
  return LSUCCESS;
}
