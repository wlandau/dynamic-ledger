/***
 *** @file copy_ledger.c
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

err_t copy_ledger(Ledger **out_ledger, Ledger *in_ledger){
  int row, field;

  if(in_ledger == NULL)
    return LFAILURE;

  new_ledger(out_ledger);
  (*out_ledger)->nrows = in_ledger->nrows;
  
  if(alloc_entries(*out_ledger) == LFAILURE)
    return LFAILURE;
  
  for(field = 0; field < NFIELDS; ++field)
    for(row = 0; row < in_ledger->nrows; ++row)  
      strcpy((*out_ledger)->entries[field][row],
             in_ledger->entries[field][row]);
  
  if(get_names(*out_ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(*out_ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS; 
}

