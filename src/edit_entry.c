/**
 * @file        edit_entry.c
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
 * @details Overwrite an entry of a Ledger object with a new entry. 
 *          Specifically, ledger->entries[field][row] is replaced with 
 *          "entry", and the other data in the Ledger object is 
 *          updated with calls to get_names and get_totals.
 */

err_t edit_entry(Ledger *ledger, char *entry, int row, int field){
  int i;
  char local_entry[ENTRYSIZE];

  /* Check for bad input */

  if(ledger == NULL || entry == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL || strlen(entry) >= ENTRYSIZE)
    return LFAILURE;

  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index \"%d\" in edit_entry().\n", row);
    return LFAILURE;
  }
  
  if(field < 0 || field >= NFIELDS){
    fprintf(stderr, "Error: illegal column index \"%d\" in edit_entry().\n", field);
    return LFAILURE;
  }
  
  if(entry == NULL){
    strcpy(ledger->entries[field][row], NIL);
    
    if(free_for_retotal(ledger) == LFAILURE)
      return LFAILURE;
      
    if(get_names(ledger) == LFAILURE)
      return LFAILURE;
        
    if(get_totals(ledger) == LFAILURE)
      return LFAILURE; 
    
    return LSUCCESS;
  }
  
  /* Sanitize "entry" and then copy it into the ledger */
  
  strcpy(local_entry, entry);
  str_strip(local_entry);
  
  if(field == AMOUNT){
    if(legal_double(local_entry) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction amount \"%s\" in edit_entry().\n", entry);
      return LFAILURE;
    }
  } else if(field == STATUS){
    if(legal_status_code(local_entry) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction status code \"%s\" in edit_entry().\n", 
              entry);
      return LFAILURE;
    }
  }
  
  if((i = col_delim_str(local_entry)) != NO_INDEX){
    fprintf(stderr, 
            "Warning: entries must not contain column delimiters. Truncating input.\n");
    local_entry[i] = '\0';
  }

  if((i = row_delim_str(local_entry)) != NO_INDEX){
    fprintf(stderr, 
            "Warning: entries must not contain row delimiters. Truncating input.\n");
    local_entry[i] = '\0';
  }
  
  strcpy(ledger->entries[field][row], local_entry);

  /* Update the rest of the data in the ledger to reflect the change. */

  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
      
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
        
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
      
  return LSUCCESS;
}
