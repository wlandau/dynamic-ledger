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

bool_t legal_amounts(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return LNO;

  for(i = 0; i < ledger->nrows; ++i)
    if(legal_double(ledger->entries[AMOUNT][i]) == LNO){
      fprintf(stderr, "Error: bad transaction amount \"%s\" at row %d.\n", 
              ledger->entries[AMOUNT][i], i + 1);
      fprintf(stderr, "Fix your ledger file.\n");
      return LNO;
    }

  return LYES;
}
