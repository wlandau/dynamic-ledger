/***
 *** @file legal_status_codes.c
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

bool_t legal_status_codes(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return LNO;

  for(i = 0; i < ledger->nrows; ++i)
    if(legal_status_code(ledger->entries[STATUS][i]) == LNO){
      fprintf(stderr, "Error: illegal status code at line %d\n", i);
      return LNO;
    }
    
  return LYES;
}
