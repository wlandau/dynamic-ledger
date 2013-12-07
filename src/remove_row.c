/***
 *** @file remove_row.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void remove_row(Ledger *ledger, int row){
  int i, j, recalculate;
  
  if(ledger == NULL)
    return;
  
  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index in remove_row().\n");
    return;
  }
  
  if(ledger->nrows < 1){
    fprintf(stderr, "Error: data already too small.\n");
    return;  
  }

  recalculate = (abs(atof(ledger->entries[AMOUNT][row])) > EPS);

  if(ledger->nrows == 1){
    fprintf(stderr, "Warning: can't remove the last row. Replacing it with a blank line.\n");
    for(i = 0; i < NFIELDS; ++i)
      strcpy(ledger->entries[i][0], NIL);
  } else {
    for(i = 0; i < NFIELDS; ++i){
      for(j = row; j < (ledger->nrows - 1); ++j)
        strcpy(ledger->entries[i][j], ledger->entries[i][j + 1]);
      free(ledger->entries[i][ledger->nrows - 1]);
    }
    --(ledger->nrows);
  }

  if(recalculate){
    free_for_retotal(ledger);
    get_names(ledger);
    get_totals(ledger); 
  }
}
 
