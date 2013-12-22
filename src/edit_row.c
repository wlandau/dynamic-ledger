/**
 * @file        edit_row.c
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
 * @details Overwrite a row of a Ledger object with a new row. 
 *          Specifically, ledger->entries[field][row] is replaced with 
 *          entries[row] for row = 0, .., NFIELDS.
 *          The other data in the Ledger object is 
 *          updated with calls to get_names and get_totals. APPEND
 *          works as in edit_entry_noretotal.
 */

err_t edit_row(Ledger *ledger, char **entries, int row, int append){

  int field, i;
  char local_entry[ENTRYSIZE];

  /* Check for bad input */

  if(ledger == NULL || entries == NULL)
    return LFAILURE;
    
  for(field = 0; field < NFIELDS; ++field)
    if(strlen(entries[field]) >= ENTRYSIZE){
      fprintf(stderr, "Error: entries[field] too big.\n");
      return LFAILURE;
    }  

  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index \"%d\" in edit_row().\n", row);
    return LFAILURE;
  }
  
  for(field = 0; field < NFIELDS; ++field)
    if(edit_entry_noretotal(ledger, entries[field], row, field, append) == LFAILURE)
      continue;
  
  if(retotal(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS;
}
