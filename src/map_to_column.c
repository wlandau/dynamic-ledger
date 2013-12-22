/**
 * @file        map_to_column.c
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
 * @details Map a single character string to multiple entries of a single column 
 *          of a Ledger object. Specifically, ledger->entries[field][rows[i]] 
 *          is replaced with "entry", for i from 0 to length(rows) - 1. Set "append"
 *          to 0 to overwrite each entry, 1 to append to the head of each entry,
 *          and 2 to append to the tail of each entry. 
 */

err_t map_to_column(Ledger *ledger, char *entry, int *rows, int nrows, int field, int append){
  int i, j;
  char local_entry[ENTRYSIZE];

  /* Check for NULL input */

  if(ledger == NULL || rows == NULL || nrows < 1)
    return LFAILURE;
  
  if(field < 0 || field >= NFIELDS){
    fprintf(stderr, "Error: illegal column index \"%d\" in map_to_column().\n", field);
    return LFAILURE;
  }
  
  if(entry == NULL){
    for(i = 0; i < nrows; ++i){
      if(rows[i] < 0 || rows[i] >= ledger->nrows)
        continue;
      if(!append)
        strcpy(ledger->entries[field][rows[i]], NIL);
    }
    
    if(free_for_retotal(ledger) == LFAILURE)
      return LFAILURE;
      
    if(get_names(ledger) == LFAILURE)
      return LFAILURE;
        
    if(get_totals(ledger) == LFAILURE)
      return LFAILURE; 
    
    return LSUCCESS;
  }
  
  /* Sanitize "entry" and then copy it into the ledger */
  
  for(i = 0; i < nrows; ++i){
    if(rows[i] < 0 || rows[i] >= ledger->nrows)
      continue;
  
    if(!append){ 
      strcpy(local_entry, entry);
    } else if(append == 1){
      strcpy(local_entry, entry);
      strncat(local_entry, ledger->entries[field][rows[i]], ENTRYSIZE - strlen(local_entry) - 1);
    } else if(append == 2){
      strcpy(local_entry, ledger->entries[field][rows[i]]);
      strncat(local_entry, entry,  ENTRYSIZE - strlen(local_entry) - 1);
    } else{
      fprintf(stderr, "Warning: bad \"append\" option. Overwriting entries.\n");
      strcpy(local_entry, entry);
    }
    
    str_strip(local_entry);
  
    if(field == AMOUNT){
      if(legal_double(local_entry) == LNO){
        fprintf(stderr, 
                "Error: illegal transaction amount \"%s\" in map_to_column().\n", entry);
        continue;
      }
    } else if(field == STATUS){
      if(legal_status_code(local_entry) == LNO){
        fprintf(stderr, 
                "Error: illegal transaction status code \"%s\" in map_to_column().\n", 
                entry);
        continue;
      }
    }
  
    if((j = col_delim_str(local_entry)) != NO_INDEX){
      fprintf(stderr, 
              "Warning: entries must not contain column delimiters. Truncating input.\n");
      local_entry[j] = '\0';
    }

    if((j = row_delim_str(local_entry)) != NO_INDEX){
      fprintf(stderr, 
              "Warning: entries must not contain row delimiters. Truncating input.\n");
      local_entry[j] = '\0';
    }
  
    strcpy(ledger->entries[field][rows[i]], local_entry);
  }

  /* Update the rest of the data in the ledger to reflect the change. */

  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
      
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
        
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
      
  return LSUCCESS;
}
