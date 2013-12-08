/***
 *** @file get_ledger_from_string.c
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

Ledger *get_ledger_from_string(char *s){
  Ledger *ledger = calloc(1, sizeof(Ledger));
  if(get_entries_from_string(ledger, s)){
    free_ledger(ledger);
    return NULL;
  }

  get_names(ledger);
  get_totals(ledger);
  return ledger;
} 
