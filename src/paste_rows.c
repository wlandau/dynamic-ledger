/***
 *** @file paste_rows.c
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

err_t paste_rows(Ledger *ledger, Ledger *clipboard, int where){
  int field, row;

  if(ledger == NULL || clipboard == NULL)
    return LFAILURE;
    
  if(clipboard->nrows < 1)
    return LSUCCESS;  
     
  if(insert_rows(ledger, where, clipboard->nrows) == LFAILURE)
    return LFAILURE;
  
  for(field = 0; field < NFIELDS; ++field)
    for(row = 0; row < clipboard->nrows; ++row)
      strcpy(ledger->entries[field][row + where], clipboard->entries[field][row]);
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;

  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS; 
}

