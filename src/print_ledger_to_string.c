/***
 *** @file print_ledger_to_string.c
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

err_t print_ledger_to_string(Ledger *ledger, char **s){
  int field, row, n = 1;
  
  if(ledger == NULL)
    return LFAILURE;

  strip_ledger(ledger);
  
  for(field = 0; field < NFIELDS; ++field)  
    for(row = 0; row < ledger->nrows; ++row)
      n += strlen(ledger->entries[field][row]) + 1;
  
  *s = calloc(n + LINESIZE, sizeof(char));
  
  for(field = 0; field < NFIELDS; ++field){
    if(field == AMOUNT)
      strcat(*s, "amount");
    else if(field == STATUS)
      strcat(*s, "status");
    else if(field == CREDIT)
      strcat(*s, "credit");
    else if(field == BANK)
      strcat(*s, "bank");
    else if(field == PARTITION)
      strcat(*s, "partition");
    else if(field == DESCRIPTION)
      strcat(*s, "description");
      
    if(field < NFIELDS - 1)
      strcat(*s, "\t");
    else
      strcat(*s, "\n");
  }  
  
  for(row = 0; row < ledger->nrows; ++row){
    for(field = 0; field < NFIELDS - 1; ++field){
      strcat(*s, ledger->entries[field][row]);
      strcat(*s, "\t");
    }
    strcat(*s, ledger->entries[NFIELDS - 1][row]);
    strcat(*s, "\n");
  }
  
  str_strip(*s);
  return LSUCCESS;
}
