/***
 *** @file modify.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void modify(Ledger *ledger, int row, int col, char *next){

  char next_local[ENTRYSIZE];
  int i;

  if(ledger == NULL)
    return;

  if(row < 0 || row >= ledger->n){
    printf("Error: illegal row index in modify().\n");
    return;
  }
  
  if(col < 0 || col >= NFIELDS){
    printf("Error: illegal column index in modify().\n");
    return;
  }
  
  if(!col)
    if(check_legal_double_modify(next))
      return;
  
  strcpy(next_local, next);
  str_strip(next_local);  
  
  if((i = contains_tabs(next_local))){
    printf("Warning: entries must not contain tabs. Truncating input.\n");
    next_local[i] = '\0';
  }
  
  strcpy(ledger->text_content[col][row], next_local);

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
}
