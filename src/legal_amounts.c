/***
 *** @file legal_amounts.c
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

int legal_amounts(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return 1;

  for(i = 0; i < ledger->nrows; ++i)
    if(legal_double(ledger->entries[AMOUNT][i], i))
      return 1;

  return 0;
}
