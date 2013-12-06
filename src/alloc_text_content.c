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

void alloc_text_content(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return;

  ledger->text_content = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->text_content[i] = malloc(ledger->n * sizeof(char*));
    for(j = 0; j < ledger->n; ++j)
      ledger->text_content[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }
}
