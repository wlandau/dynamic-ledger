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
 *          updated with calls to get_names and get_totals.
 */

err_t edit_row(Ledger *ledger, char **entries, int row){

  int field, i;
  char local_entry[ENTRYSIZE];

  /* Check for NULL input */

  if(ledger == NULL || entries == NULL)
    return LFAILURE;

  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index \"%d\" in edit_row().\n", row);
    return LFAILURE;
  }
  
  if(entries[AMOUNT] != NULL)
    if(legal_double(entries[AMOUNT]) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction amount \"%s\" in edit_row().\n", 
              entries[AMOUNT]);
      return LFAILURE;
    }

  if(entries[STATUS] != NULL){
    strcpy(local_entry, entries[STATUS]);
    str_strip(local_entry);
    if(legal_status_code(local_entry) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction status code \"%s\" in edit_row().\n", 
              local_entry);
      return LFAILURE;
    }
  }
  
  /* Sanitize entries and then copy them into the Ledger object */
  
  for(field = 0; field < NFIELDS; ++field){
  
    if(entries[field] == NULL)
      strcpy(local_entry, NIL);
    else
      strcpy(local_entry, entries[field]);

    str_strip(local_entry);
    
    if((i = col_delim_str(local_entry)) != NO_INDEX){
      fprintf(stderr, 
              "Warning: entries must not contain column delimiters. Truncating input.\n");
      local_entry[i] = '\0';
    }

    if((i = row_delim_str(entries[field])) != NO_INDEX){
      fprintf(stderr, 
              "Warning: entries must not contain row delimiters. Truncating input.\n");
      local_entry[i] = '\0';
    }
    
    strcpy(ledger->entries[field][row], local_entry);  
  } 
  
  /* Update the rest of the data in the ledger to reflect the changes. */
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
      
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
        
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
  
  return LSUCCESS;
}
