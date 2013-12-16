/***
 *** @file legal_status_codes.c
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

bool_t legal_status_codes(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return LNO;

  for(i = 0; i < ledger->nrows; ++i)
    if(legal_status_code(ledger->entries[STATUS][i]) == LNO){
      fprintf(stderr, "Error: illegal transaction status code \"%s\" at line %d\n",
              ledger->entries[STATUS][i], i + 1);
      return LNO;
    }
    
  return LYES;
}
