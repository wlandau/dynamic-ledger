/**
 * @file        insert_rows.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Insert blank rows into the "entries" member array of a 
 *          Ledger object.
 */

err_t insert_rows(Ledger *ledger, int row, int howmany){
  int i, j;
  err_t ret;
  char ***x, ***tmp;
 
  /* Check for NULL input */
 
  if(howmany < 1){
    printf("Error: number of rows inserted must be positive.\n");
    return LFAILURE;
  }
 
  if(ledger == NULL)
    return LFAILURE;
  
  if(ledger->nrows < 1){
    ledger->nrows = howmany;
    if(alloc_entries(ledger) == LFAILURE)
      return LFAILURE;
    return LSUCCESS;
  }
  
  if(row < 0 || row > ledger->nrows){
    printf("Error: illegal row index in insert_row().\n");
    return LFAILURE;
  }

  /* Allocate space for new ledger entries */
  
  x = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    x[i] = malloc((ledger->nrows + howmany) * sizeof(char*));
    for(j = 0; j < (ledger->nrows + howmany); ++j)
      x[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }

  /* Check if malloc worked */

  ret = LSUCCESS;
  if(x == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  } else {
    for(i = 0; i < NFIELDS; ++i){
      if(x[i] == NULL){
        fprintf(stderr, "Error: malloc failed.\n");
        ret = LFAILURE;
        break;
      }
      for(j = 0; j < (ledger->nrows + howmany); ++j)
        if(x[i][j] == NULL){
          fprintf(stderr, "Error: malloc failed.\n");
          ret = LFAILURE;
          break;
        }
    }
  }
  
  if(ret == LFAILURE){
    for(i = 0; i < NFIELDS; ++i){
      for(j = 0; j < (ledger->nrows + howmany); ++j)
        if(x[i][j] != NULL)
          free(x[i][j]);
      if(x[i] != NULL)
        free(x[i]);
    }
    return LFAILURE;
  }

  /* Get new 2D array of entries with the requested rows inserted */

  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < row; ++j)
      strncpy(x[i][j], ledger->entries[i][j], (ENTRYSIZE - 1) * sizeof(char));

    strncpy(x[i][row], NIL, (ENTRYSIZE - 1) * sizeof(char));

    for(j = row + howmany; j < (ledger->nrows + howmany); ++j)
      strncpy(x[i][j], ledger->entries[i][j - howmany], (ENTRYSIZE - 1) * sizeof(char));
  }

  /* Clean up and return */

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

