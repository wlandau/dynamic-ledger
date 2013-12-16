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

  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;  
    
  order = calloc(ledger->nrows, sizeof(int));
  row = ledger->nrows;
  for(i = 0; i < ledger->nrows; ++i)
    if(str_equal(ledger->entries[STATUS][i], REMOVE)){
      ++order[i];
      --row;
    }

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
  
  for(field = 0; field < NFIELDS; ++field)
    for(i = row; i < ledger->nrows; ++i)
      free(ledger->entries[field][i]);
  ledger->nrows = row;
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS;
}
