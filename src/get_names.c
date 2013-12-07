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
  char **s = malloc(ledger->nrows * sizeof(char*));

  for(i = 0; i < ledger->nrows; ++i){
    s[i] = calloc(ENTRYSIZE, sizeof(char));
    strcpy(s[i], ledger->entries[CREDIT][i]);
  }
     
  unique(s, ledger->nrows, &ledger->credits, &ledger->ncredits);
    
  for(i = 0; i < ledger->nrows; ++i)
    strcpy(s[i], ledger->entries[BANK][i]);
  
  unique(s, ledger->nrows, &ledger->banks, &ledger->nbanks);
  
  ledger->npartitions = calloc(ledger->nbanks, sizeof(int*));
  ledger->partitions = malloc(ledger->nbanks * sizeof(char***));
        
  for(i = 0; i < ledger->nbanks; ++i){
    for(j = 0; j < ledger->nrows; ++j){         
      strcpy(s[j], ledger->entries[PARTITION][j]);
      if(!str_equal(ledger->banks[i], ledger->entries[BANK][j]))
        strcpy(s[j], NIL);
    }
     
    unique(s, ledger->nrows, &(ledger->partitions[i]), &(ledger->npartitions[i]));
  }
  
  for(i = 0; i < ledger->nrows; ++i)
    free(s[i]);
  free(s);
}
