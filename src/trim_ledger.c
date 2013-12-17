/***
 *** @file trim_ledger.c
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

err_t trim_ledger(Ledger *ledger){
  int row;

  if(ledger == NULL)
    return LFAILURE;

  for(row = 0; row < ledger->nrows; ++row)
    if((small_norm(atof(ledger->entries[AMOUNT][row])) == LYES) &&
       !str_equal(ledger->entries[STATUS][row], LOCKED))
      strcpy(ledger->entries[STATUS][row], REMOVE);    
   
  if(remove_rows(ledger) == LFAILURE)
    return LFAILURE;

  return LSUCCESS;
}
