/***
 *** @file strip_ledger.c
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

err_t strip_ledger(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->nrows < 1)
    return LFAILURE;

  for(i = 0; i < NFIELDS; ++i)
    for(j = 0; j < ledger->nrows; ++j)
      str_strip(ledger->entries[i][j]);
  
  return LSUCCESS;
}
