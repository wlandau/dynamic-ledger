/***
 *** @file remove_rows.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t remove_rows(Ledger *ledger){
  int i, *order, row, field;

  /* CHECK FOR NULL INPUT */

  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;  
    
  /* ALLOCATE SPACE FOR PERMUTATION AND CHECK IF MALLOC WORKED */
    
  order = calloc(ledger->nrows, sizeof(int));
  if(order == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  /* CALCULATE PERMUTATION */  
  
  row = ledger->nrows;
  for(i = 0; i < ledger->nrows; ++i)
    if(str_equal(ledger->entries[STATUS][i], REMOVE)){
      ++order[i];
      --row;
    }

  /* PERMUTE ROWS FOR REMOVAL */ 

  if(permute_rows(ledger, order) == LFAILURE){
    free(order);
    return LFAILURE;
  }
  free(order);

  if(!row){
    fprintf(stderr, "Warning: cannot remove all rows. Leaving one blank row instead.\n");
    for(field = 0; field < NFIELDS; ++field)
      strcpy(ledger->entries[field][0], NIL);
    ++row;
  }
  
  /* FREE THE ROWS AT THE BOTTOM */ 
  
  for(field = 0; field < NFIELDS; ++field)
    for(i = row; i < ledger->nrows; ++i)
      free(ledger->entries[field][i]);
  ledger->nrows = row;

  /* RECALCULATE NAMES AND TOTALS */ 
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS;
}
