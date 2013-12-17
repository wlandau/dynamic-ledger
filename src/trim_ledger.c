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
    
  if(ledger->nrows < 1 || ledger->entries == NULL)
    return LFAILURE;  

  for(row = 0; row < ledger->nrows; ++row)
    if(small_norm(atof(ledger->entries[AMOUNT][row])) == LYES)
      strcpy(ledger->entries[STATUS][row], REMOVE);    
   
  if(remove_rows(ledger) == LFAILURE)
    return LFAILURE;

  return LSUCCESS;
}
