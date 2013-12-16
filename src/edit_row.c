/***
 *** @file edit_row.c
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

err_t edit_row(Ledger *ledger, char **entries, int row){

  int field, i;
  char local_entry[ENTRYSIZE];

  if(ledger == NULL)
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
  
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
  
  return LSUCCESS;
}
