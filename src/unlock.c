/**
 * @file        unlock.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License >= 3.0 (See COPYING.txt)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Unlocks all cleared transactions. Specifically,
 *          this function changes the status of all transactions
 *          with status LOCKED to status NIL:         
 */

err_t unlock(Ledger *ledger){
  int row;

  /* Check for NULL input */

  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL || ledger->nrows < 1)
    return LFAILURE;
    
  /* Change all LOCKED status codes to NIL */  
    
  for(row = 0; row < ledger->nrows; ++row)
    if(str_equal(ledger->entries[STATUS][row], LOCKED))
      strcpy(ledger->entries[STATUS][row], NIL);

  return LSUCCESS;
}
