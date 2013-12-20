/**
 * @file        strip_ledger.c
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
 * @details Removes leading and trailing whitespace from every entry
 *          of a Ledger object. Specifically, str_strip is called on
 *          every character string in the "entries" member array of the
 *          Ledger object.
 */
err_t strip_ledger(Ledger *ledger){
  int i, j;
  
  /* Check for NULL input */
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->entries == NULL)
    return LSUCCESS;

  /* Call str_strip to remove the leading and trailing whitespace from every entry */

  for(i = 0; i < NFIELDS; ++i)
    for(j = 0; j < ledger->nrows; ++j)
      if(str_strip(ledger->entries[i][j]) == LFAILURE)
        return LFAILURE;
  
  return LSUCCESS;
}
