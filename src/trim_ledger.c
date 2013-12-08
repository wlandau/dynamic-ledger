/***
 *** @file trim_ledger.c
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

void trim_ledger(Ledger *ledger){
  int i; 

  if(ledger == NULL)
    return;

  for(i = (ledger->nrows - 1); i >= 0; --i)
    if(abs(atof(ledger->entries[AMOUNT][i])) < EPS)
      remove_row(ledger, i);
}
