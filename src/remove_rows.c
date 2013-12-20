/**
 * @file remove_rows.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Remove the rows in a Ledger object with 
 *          transaction status code REMOVE. The rows with this
 *          status are sent to the bottom of the "entries" array
 *          of the Ledger object and then freed. 
 */
err_t remove_rows(Ledger *ledger){
  int i, *order, row, field;

  /* Check for NULL input */

  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;  
    
  /* Allocate space for permutation and check if malloc worked */
    
  order = calloc(ledger->nrows, sizeof(int));
  if(order == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }
  
  /* Calculate permutation to send rows marked for removal to the bottom */  
  
  row = ledger->nrows;
  for(i = 0; i < ledger->nrows; ++i)
    if(str_equal(ledger->entries[STATUS][i], REMOVE)){
      ++order[i];
      --row;
    }

  /* Permute rows to bring rows marked for removal to the bottom */ 

  if(permute_rows(ledger, order) == LFAILURE){
    free(order);
    return LFAILURE;
  }
  free(order);
  
  /* Free rows at the bottom */ 
  
  if(!row){
    if(free_entries(ledger) == LFAILURE)
      return LFAILURE;
    return LSUCCESS;  
  } else {
    for(field = 0; field < NFIELDS; ++field)
      for(i = row; i < ledger->nrows; ++i)
        free(ledger->entries[field][i]);
    ledger->nrows = row;
  }
  
  /* Update the Ledger object to reflect the change */ 
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS;
}
