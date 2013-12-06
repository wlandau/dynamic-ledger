/***
 *** @file free_ledger.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_ledger(Ledger *ledger){
  int i, j;

  if(ledger == NULL)
    return;

  if(ledger->filename != NULL)
    free(ledger->filename);
    
  if(ledger->text_content != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(ledger->text_content[i] != NULL){
        for(j = 0; j < ledger->n; ++j)
          if(ledger->text_content[i][j] != NULL)
            free(ledger->text_content[i][j]);
        free(ledger->text_content[i]);
      }
    }
    free(ledger->text_content);
  }
  
  free_for_retotal(ledger);
  free(ledger);
}
