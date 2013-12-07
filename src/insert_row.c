/***
 *** @file insert_row.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_row(Ledger *ledger, int row){
  int i, j;
  char ***x, ***tmp;
 
  if(ledger == NULL)
    return;
    
  if(row < 0 || row > ledger->nrows){
    printf("Error: illegal row index in insert_row().\n");
    return;
  }

  x = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    x[i] = malloc((ledger->nrows + 1) * sizeof(char*));
    for(j = 0; j < (ledger->nrows + 1); ++j)
      x[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }

  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < row; ++j)
      strcpy(x[i][j], ledger->entries[i][j]);

    strcpy(x[i][row], NIL);

    for(j = row + 1; j < (ledger->nrows + 1); ++j)
      strcpy(x[i][j], ledger->entries[i][j - 1]);
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
  
  ++(ledger->nrows); 
}

