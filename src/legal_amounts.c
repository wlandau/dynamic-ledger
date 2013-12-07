/***
 *** @file legal_amounts.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int legal_amounts(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return 1;

  for(i = 0; i < ledger->nrows; ++i)
    if(check_legal_double(ledger->entries[AMOUNT][i], i))
      return 1;

  return 0;
}