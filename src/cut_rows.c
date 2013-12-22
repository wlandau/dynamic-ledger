/**
 * @file        cut_rows.c
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
 * @details Cuts the selected rows (transactions). Specifically, copy_rows
 *          is called, and then the copied rows are removed from the original
 *          Ledger object.
 */
err_t cut_rows(Ledger *ledger, Ledger **clipboard, int *rows, int howmany){
  int row;

  /* Check for null input */

  if(ledger == NULL || rows == NULL || howmany < 1)
    return LFAILURE;

  if(ledger->entries == NULL)
    return LFAILURE;
     
  /* Call copy_rows */
     
  if(copy_rows(ledger, clipboard, rows, howmany) == LFAILURE)
    return LFAILURE;
  
  /* Remove copied rows from ledger */
  
  for(row = 0; row < howmany; ++row)
    strlcpy(ledger->entries[STATUS][rows[row]], REMOVE, (ENTRYSIZE - 1) * sizeof(char));
    
  if(remove_rows(ledger) == LFAILURE)
    return LFAILURE;

  return LSUCCESS; 
}

