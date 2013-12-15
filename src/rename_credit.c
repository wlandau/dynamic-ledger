/***
 *** @file rename_credit.c
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

err_t rename_credit(Ledger *ledger, char *from, char *to){
  int i;

  if(ledger == NULL)
    return LFAILURE;

  for(i = 0; i < ledger->nrows; ++i)
    if(str_equal(ledger->entries[CREDIT][i], from))
      strcpy(ledger->entries[CREDIT][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
  
  return LSUCCESS;
}
