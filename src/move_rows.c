/**
 * @file move_rows.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/** 
 * @details Move the rows (transactions) of the "entries" member array
 *          of a Ledger object to another location (row) in the same array.
 *          The workhorse of this function is permute_rows.
 */
err_t move_rows(Ledger *ledger, int *rows, int nrows, int moveto){
  int i, *order;
  
  /* Check for NULL input */
  
  if(ledger == NULL || rows == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
    
  if(ledger->nrows < 1)
    return LFAILURE;
  
  /* Allocate space for permutation order and check if malloc worked */
  
  order = calloc(ledger->nrows, sizeof(int));
  if(order == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  /* Calculate permutation */
  
  for(i = moveto; i < ledger->nrows; ++i)
    order[i] = 2;
  
  for(i = 0; i < nrows; ++i)
    order[rows[i]] = 1;

  /* Apply permutation */
  
  if(permute_rows(ledger, order) == LFAILURE){
    free(order);
    return LFAILURE;
  }
  
  /* Clean up and return */
  
  free(order);
  return LSUCCESS;
}
