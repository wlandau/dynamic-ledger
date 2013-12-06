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
  
  if(row < 0 || row >= ledger->n){
    printf("Error: illegal row index in remove_row().\n");
    return;
  }
  
  if(ledger->n < 1){
    printf("Error: data already too small.\n");
    return;  
  }

  recalculate = (abs(atof(ledger->text_content[AMOUNT][row])) > EPS);

  if(ledger->n == 1){
    printf("Warning: can't remove the last row. Replacing it with a blank line.\n");
    for(i = 0; i < NFIELDS; ++i)
      strcpy(ledger->text_content[i][0], NIL);
  } else {
    for(i = 0; i < NFIELDS; ++i){
      for(j = row; j < (ledger->n - 1); ++j)
        strcpy(ledger->text_content[i][j], ledger->text_content[i][j + 1]);
      free(ledger->text_content[i][ledger->n - 1]);
    }
    --(ledger->n);
  }

  if(recalculate){
    free_for_retotal(ledger);
    get_names(ledger);
    get_totals(ledger); 
  }
}
 
