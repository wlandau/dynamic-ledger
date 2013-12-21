/**
 * @file        rename_partition.c
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
 * @details Safely renames a partition of a bank account and
 *          updates the other data in the Ledger
 *          object to reflect  the change. 
 */
err_t rename_partition(Ledger *ledger, char *bank, char *from, char *to){
  int i;

  /* Check for NULL input */
  
  if(ledger == NULL)
    return LFAILURE;
  
  /* Rename the partition */
  
  for(i = 0; i < ledger->nrows; ++i)
    if(str_equal(ledger->entries[BANK][i], bank) && 
       str_equal(ledger->entries[PARTITION][i], from))
      strcpy(ledger->entries[PARTITION][i], to);

  /* Update the rest of the data in the Ledger object to reflect the change */
      
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
  
  return LSUCCESS; 
}
