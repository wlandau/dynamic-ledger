/***
 *** @file trim_ledger.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t trim_ledger(Ledger *ledger){
  int row;

  if(ledger == NULL)
    return LFAILURE;

  for(row = 0; row < ledger->nrows; ++row)
    if(fabs(atof(ledger->entries[AMOUNT][row])) < EPS)
      strcpy(ledger->entries[STATUS][row], REMOVE);    
   
  remove_rows(ledger);
  return LSUCCESS;
}
