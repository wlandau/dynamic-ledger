/***
 *** @file new_ledger.c
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

Ledger *new_ledger(){
  Ledger *ledger = malloc(sizeof(Ledger));
  ledger->nrows = 1;
  ledger->filename = NULL;
  alloc_entries(ledger);
  get_names(ledger);
  get_totals(ledger);   
  return ledger; 
}

