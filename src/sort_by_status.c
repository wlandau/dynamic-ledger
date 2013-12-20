/**
 * @file sort_by_status.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Sorts the rows (transactions) of a Ledger object
 *          such that the transactions that have not completely 
 *          cleared rise to the top of the ledger. This is useful
 *          because delayed transactions have status codes that
 *          will eventually need to be changed. Calls permute_rows
 *          to do the job.
 */
err_t sort_by_status(Ledger *ledger, int sort_locked){
  int i, *order;
  
  /* Check for NULL input */
  
  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
    
  if(ledger->nrows < 1)
    return LFAILURE;
  
  /* Allocate space for permutation and check if malloc worked */
  
  order = calloc(ledger->nrows, sizeof(int));
  if(order == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  /* Compute the permutation */
  
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
  
  /* Carry out the permutation */
  
  if(permute_rows(ledger, order) == LFAILURE){
    free(order);
    return LFAILURE;
  }
  
  /* Clean up and return */
  
  free(order);
  return LSUCCESS;
}
