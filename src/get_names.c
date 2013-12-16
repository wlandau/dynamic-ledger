/***
 *** @file get_names.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t get_names(Ledger *ledger){
  int i, j;
  char **s;
  
  if(ledger == NULL) 
    return LFAILURE;
    
  if(ledger->nrows < 1)
    return LFAILURE;
  
  s = malloc(ledger->nrows * sizeof(char*));
  for(i = 0; i < ledger->nrows; ++i)
    s[i] = calloc(ENTRYSIZE, sizeof(char));

  unique(ledger->entries[CREDIT], ledger->nrows, &ledger->credits, &ledger->ncredits);
  unique(ledger->entries[BANK], ledger->nrows, &ledger->banks, &ledger->nbanks);  
  
  ledger->npartitions = calloc(ledger->nbanks, sizeof(int*));
  ledger->partitions = malloc(ledger->nbanks * sizeof(char***));
        
  for(i = 0; i < ledger->nbanks; ++i){
    for(j = 0; j < ledger->nrows; ++j){    
      if(str_equal(ledger->banks[i], ledger->entries[BANK][j]))     
        strcpy(s[j], ledger->entries[PARTITION][j]);
      else
        strcpy(s[j], NIL);
    }
     
    unique(s, ledger->nrows, &(ledger->partitions[i]), &(ledger->npartitions[i]));
  }
  
  for(i = 0; i < ledger->nrows; ++i)
    free(s[i]);
  free(s);
  
  return LSUCCESS;
}
