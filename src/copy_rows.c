/***
 *** @file copy_rows.c
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

err_t copy_rows(Ledger *ledger, Ledger **clipboard, int *rows, int howmany){
  int row, field;

  if(ledger == NULL || rows == NULL || howmany < 1)
    return LFAILURE;

  if(new_ledger(clipboard) == LFAILURE)
    return LFAILURE;
     
  (*clipboard)->nrows = howmany;
  
  if(alloc_entries(*clipboard) == LFAILURE)
    return LFAILURE;

  for(field = 0; field < NFIELDS; ++field)
    for(row = 0; row < howmany; ++row)
       strcpy((*clipboard)->entries[field][row], ledger->entries[field][rows[row]]);
  
  return LSUCCESS; 
}

