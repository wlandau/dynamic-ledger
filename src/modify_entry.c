/***
 *** @file modify_entry.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t modify_entry(Ledger *ledger, int row, int col, char *next){
  int i;
  char *next_local;

  if(ledger == NULL)
    return LFAILURE;

  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index \"%d\" in modify_entry().\n", row);
    return LFAILURE;
  }
  
  if(col < 0 || col >= NFIELDS){
    fprintf(stderr, "Error: illegal column index \"%d\" in modify_entry().\n", col);
    return LFAILURE;
  }
  
  next_local = malloc(ENTRYSIZE * sizeof(char));
  strcpy(next_local, next);
  str_strip(next_local); 
  
  if(col == AMOUNT){
    if(legal_double(next_local) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction amount \"%s\" in modify_entry().\n", next);
      free(next_local);
      return LFAILURE;
    }
  } else if(col == STATUS){
    if(legal_status_code(next_local) == LNO){
      fprintf(stderr, 
              "Error: illegal transaction status code \"%s\" in modify_entry().\n", 
              next);
      free(next_local);
      return LFAILURE;
    }
  }
  
  if((i = col_delim_str(next_local)) != NO_INDEX){
    fprintf(stderr, 
            "Warning: entries must not contain column delimiters. Truncating input.\n");
    next_local[i] = '\0';
  }

  if((i = row_delim_str(next_local)) != NO_INDEX){
    fprintf(stderr, 
            "Warning: entries must not contain row delimiters. Truncating input.\n");
    next_local[i] = '\0';
  }
  
  strcpy(ledger->entries[col][row], next_local);

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
  
  free(next_local);
  return LSUCCESS;
}
