/**
 * @file        trim_ledger.c
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
 * @details Remove rows (transactions) with transaction amounts of
 *          zero. These empty transactions do not actually contribute
 *          to the content of the ledger. They are marked for removal
 *          and then removed with remove_rows.
 */

err_t trim_ledger(Ledger *ledger){
  int row;

  /* Check for NULL input */

  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->nrows < 1 || ledger->entries == NULL)
    return LFAILURE;  

  /* Mark rows with transaction amounts of zero for removal */

  for(row = 0; row < ledger->nrows; ++row)
    if(small_norm(atof(ledger->entries[AMOUNT][row])) == LYES)
      strncpy(ledger->entries[STATUS][row], REMOVE, (ENTRYSIZE - 1) * sizeof(char));    
   
  /* Remove rows with transaction amounts of zero */ 
   
  if(remove_rows(ledger) == LFAILURE)
    return LFAILURE;

  return LSUCCESS;
}
