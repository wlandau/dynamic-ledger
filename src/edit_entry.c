/***
 *** @file edit_entry.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t edit_entry(Ledger *ledger, char *entry, int row, int field){
  int i;
  char local_entry[ENTRYSIZE];

  if(ledger == NULL)
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
    
    free_for_retotal(ledger);
    get_names(ledger);
    get_totals(ledger); 
    
    return LSUCCESS;
  }
  
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

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
  
  return LSUCCESS;
}
