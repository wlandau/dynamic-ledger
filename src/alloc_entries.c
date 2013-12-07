/***
 *** @file alloc_text_content.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void alloc_entries(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return;

  ledger->entries = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->entries[i] = malloc(ledger->nrows * sizeof(char*));
    for(j = 0; j < ledger->nrows; ++j)
      ledger->entries[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }
}
