/***
 *** @file get_names.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_names(Ledger *ledger){
  int i, j;
  char **s = malloc(ledger->n * sizeof(char*));

  for(i = 0; i < ledger->n; ++i){
    s[i] = calloc(ENTRYSIZE, sizeof(char));
    strcpy(s[i], ledger->text_content[CREDIT][i]);
  }
     
  unique(s, ledger->n, &ledger->credit, &ledger->ncredit);
    
  for(i = 0; i < ledger->n; ++i)
    strcpy(s[i], ledger->text_content[BANK][i]);
  
  unique(s, ledger->n, &ledger->bank, &ledger->nbank);
  
  ledger->npartition = calloc(ledger->nbank, sizeof(int*));
  ledger->partition = malloc(ledger->nbank * sizeof(char***));
        
  for(i = 0; i < ledger->nbank; ++i){
    for(j = 0; j < ledger->n; ++j){         
      strcpy(s[j], ledger->text_content[PARTITION][j]);
      if(!str_equal(ledger->bank[i], ledger->text_content[BANK][j]))
        strcpy(s[j], NIL);
    }
     
    unique(s, ledger->n, &(ledger->partition[i]), &(ledger->npartition[i]));
  }
  
  for(i = 0; i < ledger->n; ++i)
    free(s[i]);
  free(s);
}
