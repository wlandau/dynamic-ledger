/***
 *** @file cut_rows.c
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

err_t cut_rows(Ledger *ledger, Ledger **clipboard, int *rows, int howmany){
  int row;

  if(ledger == NULL || rows == NULL || howmany < 1)
    return LFAILURE;
     
  copy_rows(ledger, clipboard, rows, howmany);
  
  for(row = 0; row < howmany; ++row)
    strcpy(ledger->entries[STATUS][rows[row]], REMOVE);
    
  remove_rows(ledger);
  
  return LSUCCESS; 
}

