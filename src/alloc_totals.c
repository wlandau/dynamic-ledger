/***
 *** @file alloc_totals.c
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

err_t alloc_totals(Ledger *ledger){
  int i;
  err_t ret;

  /* check for null input */
  
  if(ledger == NULL || ledger->credits == NULL || 
     ledger->banks == NULL || ledger->npartitions == NULL)
    return LFAILURE;
  
  /* allocate totals */
  
  if(ledger->credit_totals == NULL){
    ledger->credit_totals = malloc(ledger->ncredits * sizeof(double*));
    for(i = 0; i < ledger->ncredits; ++i)
      ledger->credit_totals[i] = calloc(N_TOTALS, sizeof(double));
  }
    
  if(ledger->bank_totals == NULL){
    ledger->bank_totals = malloc(ledger->nbanks * sizeof(double*));  
    for(i = 0; i < ledger->nbanks; ++i)
      ledger->bank_totals[i] = calloc(N_TOTALS, sizeof(double));
  }
  
  if(ledger->partition_totals == NULL){
    ledger->partition_totals = malloc(ledger->nbanks * sizeof(double*));
    for(i = 0; i < ledger->nbanks; ++i)
      ledger->partition_totals[i] = calloc(ledger->npartitions[i], sizeof(double));
  }
  
  /* check if malloc worked */
  
  ret = LSUCCESS;
  if(ledger->credit_totals == NULL || 
     ledger->bank_totals == NULL || 
     ledger->partition_totals == NULL){
    fprintf(stderr, "Error: malloc failed\n"); 
    ret = LFAILURE; 
  } else {
    for(i = 0; i < ledger->ncredits; ++i){
      if(ledger->credit_totals[i] == NULL){
        fprintf(stderr, "Error: malloc failed\n"); 
        ret = LFAILURE;
        break;
      }
    }
  
    for(i = 0; i < ledger->nbanks; ++i){
      if(ledger->bank_totals[i] == NULL || ledger->partition_totals[i] == NULL){
        fprintf(stderr, "Error: malloc failed\n"); 
        ret = LFAILURE;
        break;
      }  
    }
  }
  
  return ret;
}
