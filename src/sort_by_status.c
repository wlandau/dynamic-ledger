/***
 *** @file sort_by_status.c
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

err_t sort_by_status(Ledger *ledger, int sort_locked){
  int i, *order;
  
  /* CHECK FOR NULL INPUT */
  
  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
    
  if(ledger->nrows < 1)
    return LFAILURE;
  
  /* ALLOCATE SPACE FOR PERMUTATION AND CHECK IF MALLOC WORKED */
  
  order = calloc(ledger->nrows, sizeof(int));
  if(order == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  /* COMPUTE THE PERMUTATION */
  
  for(i = 0; i < ledger->nrows; ++i){
    if(str_equal(ledger->entries[STATUS][i], CREDIT_NOT_THERE_YET))
      order[i] = 0;
    else if(str_equal(ledger->entries[STATUS][i], CREDIT_PENDING))
      order[i] = 1;
    else if(str_equal(ledger->entries[STATUS][i], CREDIT_CHARGED))
      order[i] = 2;
    else if(str_equal(ledger->entries[STATUS][i], NOT_THERE_YET))
      order[i] = 3;
    else if(str_equal(ledger->entries[STATUS][i], PENDING))
      order[i] = 4;
    else if(str_equal(ledger->entries[STATUS][i], LOCKED) && (sort_locked == LYES))
      order[i] = 5;
    else
      order[i] = 6;
  }
  
  /* CARRY OUT THE PERMUTATION */
  
  if(permute_rows(ledger, order) == LFAILURE){
    free(order);
    return LFAILURE;
  }
  
  /* CLEAN UP AND EXIT */
  
  free(order);
  return LSUCCESS;
}
