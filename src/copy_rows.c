/**
 * @file        copy_rows.c
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
 * @details Copies selected rows (transactions). Specifically, the 
 *          rows (transactions) whose indices are in "rows" are 
 *          copied from "ledger" to "clipboard". The clipboard
 *          is overwritten in this function.
 */
err_t copy_rows(Ledger *ledger, Ledger **clipboard, int *rows, int howmany){
  int row, field;

  /* Check for null input */

  if(ledger == NULL || rows == NULL || howmany < 1)
    return LFAILURE;

  if(ledger->entries == NULL)
    return LFAILURE;
    
  if(howmany > ledger->nrows){
    fprintf(stderr,
      "Error: number of rows to copy is greater than the total number of rows.\n");
    return LFAILURE;
  }

  /* Clear clipboard */

  free_ledger(clipboard);

  if(new_ledger(clipboard) == LFAILURE)
    return LFAILURE;
     
  /* Fill clipboard with the relevant rows of ledger */
     
  (*clipboard)->nrows = howmany;
  
  if(alloc_entries(*clipboard) == LFAILURE)
    return LFAILURE;

  for(field = 0; field < NFIELDS; ++field)
    for(row = 0; row < howmany; ++row)
       strcpy((*clipboard)->entries[field][row], ledger->entries[field][rows[row]]);
  
  return LSUCCESS; 
}

