/***
 *** @file get_ledger_from_stream.c
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

Ledger *get_ledger_from_stream(FILE *fp){
  Ledger *ledger;
  
  if(fp == NULL)
    return NULL;

  ledger = calloc(1, sizeof(Ledger));
   
  if(get_entries_from_stream(ledger, fp)){
    free_ledger(ledger);
    return NULL;
  } 
  
  get_names(ledger);
  get_totals(ledger);   
  
  return ledger; 
}
