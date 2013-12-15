/***
 *** @file insert_rows.c
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

err_t insert_rows(Ledger *ledger, int row, int howmany){
  int i, j;
  char ***x, ***tmp;
 
  if(howmany < 1){
    printf("Error: number of rows inserted must be positive.\n");
    return LFAILURE;
  }
 
  if(ledger == NULL)
    return LFAILURE;
    
  if(row < 0 || row > ledger->nrows){
    printf("Error: illegal row index in insert_row().\n");
    return LFAILURE;
  }

  x = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    x[i] = malloc((ledger->nrows + howmany) * sizeof(char*));
    for(j = 0; j < (ledger->nrows + howmany); ++j)
      x[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }

  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < row; ++j)
      strcpy(x[i][j], ledger->entries[i][j]);

    strcpy(x[i][row], NIL);

    for(j = row + howmany; j < (ledger->nrows + howmany); ++j)
      strcpy(x[i][j], ledger->entries[i][j - howmany]);
  }

  tmp = ledger->entries;
  ledger->entries = x;
  
  if(tmp != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(tmp[i] != NULL){
        for(j = 0; j < ledger->nrows; ++j)
          if(tmp[i][j] != NULL)
            free(tmp[i][j]);
        free(tmp[i]);
      }
    }
    free(tmp);
  }
  
  ledger->nrows += howmany; 
  return LSUCCESS;
}

