/**
 * @file        insert_filled_rows.c
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
 * @details Insert a multiple copies of a new filled 
 *          row at "row" in the ledger.
 */

err_t insert_filled_rows(Ledger *ledger, char **entries, int row, int howmany){

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

  if(row < 0 || row > ledger->nrows){
    fprintf(stderr, "Error: illegal row index \"%d\" in edit_row().\n", row);
    return LFAILURE;
  }
  
  /* insert new blank rows */
  
  insert_rows(ledger, row, howmany);
  
  /* fill that blank row with input */
  
  for(field = 0; field < NFIELDS; ++field)
    for(i = 0; i < howmany; ++i)
      if(edit_entry_noretotal(ledger, entries[field], row + i, field, 0) 
         == LFAILURE)
        continue;
  
  if(retotal(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS;
}
