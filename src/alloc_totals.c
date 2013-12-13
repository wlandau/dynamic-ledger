/***
 *** @file alloc_totals.c
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

err_t alloc_totals(Ledger *ledger){
  int i;

  if(ledger == NULL || ledger->credits == NULL || 
     ledger->banks == NULL || ledger->npartitions == NULL)
    return LFAILURE;
  
  ledger->credit_totals = calloc(ledger->ncredits, sizeof(double*));
  for(i = 0; i < ledger->ncredits; ++i)
    ledger->credit_totals[i] = calloc(4, sizeof(double));
      
  ledger->bank_totals = calloc(ledger->nbanks, sizeof(double*));  
  for(i = 0; i < ledger->nbanks; ++i)
    ledger->bank_totals[i] = calloc(4, sizeof(double));
  
  ledger->partition_totals = malloc(ledger->nbanks * sizeof(double*));
  for(i = 0; i < ledger->nbanks; ++i)
    ledger->partition_totals[i] = calloc(ledger->npartitions[i], sizeof(double));

  return LSUCCESS;
}
