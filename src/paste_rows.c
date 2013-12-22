/**
 * @file        paste_rows.c
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
 * @details Pastes rows (transactions) in "clipboard" into "ledger"
 *          at row "where". insert_rows is called, and then the 
 *          relevant rows are copied in.
 */

err_t paste_rows(Ledger *ledger, Ledger *clipboard, int where){
  int field, row;

  /* Check for NULL input */

  if(ledger == NULL || clipboard == NULL)
    return LFAILURE;
    
  if(clipboard->nrows < 1)
    return LSUCCESS;  
     
  /* Insert the blank rows to copy into */
     
  if(insert_rows(ledger, where, clipboard->nrows) == LFAILURE)
    return LFAILURE;

  /* Copy the rows from "clipboard" into the new blank rows */
  
  for(field = 0; field < NFIELDS; ++field)
    for(row = 0; row < clipboard->nrows; ++row)
      if(strlen(clipboard->entries[field][row]) < ENTRYSIZE)
        strcpy(ledger->entries[field][row + where], clipboard->entries[field][row]);

  /* Update the rest of the data in ledger to reflect the changes */
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;

  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS; 
}

