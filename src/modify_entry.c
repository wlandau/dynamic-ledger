/***
 *** @file modify_entry.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

void modify_entry(Ledger *ledger, int row, int col, char *next){

  char next_local[ENTRYSIZE];
  int i;

  if(ledger == NULL)
    return;

  if(row < 0 || row >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index in modify_entry().\n");
    return;
  }
  
  if(col < 0 || col >= NFIELDS){
    fprintf(stderr, "Error: illegal column index in modify_entry().\n");
    return;
  }
  
  if(!col)
    if(check_legal_double_modify_entry(next))
      return;
  
  strcpy(next_local, next);
  str_strip(next_local);  
  
  if((i = contains_column_delim(next_local))){
    fprintf(stderr, "Warning: entries must not contain tabs. Truncating input.\n");
    next_local[i] = '\0';
  }
  
  strcpy(ledger->entries[col][row], next_local);

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
}
