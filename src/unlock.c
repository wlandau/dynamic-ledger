/***
 *** @file unlock.c
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

err_t unlock(Ledger *ledger){
  int row;

  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL || ledger->nrows < 1)
    return LSUCCESS;
    
  for(row = 0; row < ledger->nrows; ++row)
    if(str_equal(ledger->entries[STATUS][row], LOCKED))
      strcpy(ledger->entries[STATUS][row], NIL);

  return LSUCCESS;
}
