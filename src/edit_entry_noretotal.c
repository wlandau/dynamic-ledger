/**
 * @file        edit_entry_noretotal.c
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
 *          NOT updated. Set "append" to 0 to overwrite
 *          each entry, 1 to append to the head of each entry,
 *          and 2 to append to the tail of each entry. 
 */

err_t edit_entry_noretotal(Ledger *ledger, char *entry, int row, int field, int append){
  int i;
  char local_entry[ENTRYSIZE];

  /* Check for NULL input */

  if(ledger == NULL)
    return LFAILURE;

  if(ledger->entries == NULL || strlen(entry) >= ENTRYSIZE)
    return LFAILURE;

  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index \"%d\" in edit_entry_noretotal().\n", row);
    return LFAILURE;
  }
  
  if(field < 0 || field >= NFIELDS){
    fprintf(stderr, "Error: illegal column index \"%d\" in edit_entry_noretotal().\n", field);
    return LFAILURE;
  }
  
  if(entry == NULL){
    strcpy(ledger->entries[field][row], NIL);
    return LSUCCESS;
  }
  
  /* Sanitize "entry" and then copy it into the ledger */
  
  if(entry == NULL){
    strcpy(local_entry, NIL);
  } else if(!append){ 
    strcpy(local_entry, entry);
  } else if(append == 1){
    strcpy(local_entry, entry);
    strncat(local_entry, ledger->entries[field][row], ENTRYSIZE - strlen(local_entry) - 1);
  } else if(append == 2){
    if(strlen(ledger->entries[field][row]) < ENTRYSIZE)
      strcpy(local_entry, ledger->entries[field][row]);
    strncat(local_entry, entry,  ENTRYSIZE - strlen(local_entry) - 1);
  } else{
    fprintf(stderr, "Warning: bad \"append\" option. Overwriting entries.\n");
    strcpy(local_entry, entry);
  }
    
  str_strip(local_entry);
  
  if(field == AMOUNT){
    if(legal_double(local_entry) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction amount \"%s\" in edit_entry_noretotal().\n", entry);
      return LFAILURE;
    }
  } else if(field == STATUS){
    if(legal_status_code(local_entry) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction status code \"%s\" in edit_entry_noretotal().\n", 
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
      
  return LSUCCESS;
}
