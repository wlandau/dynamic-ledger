/***
 *** @file get_totals.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_totals(Ledger *ledger){
  int i, j, k;
  double amount;
  char *status;

  ledger->credit_totals = calloc(ledger->ncredit, sizeof(double*));
  for(i = 0; i < ledger->ncredit; ++i)
    ledger->credit_totals[i] = calloc(4, sizeof(double));
      
  ledger->bank_totals = calloc(ledger->nbank, sizeof(double*));  
  for(i = 0; i < ledger->nbank; ++i)
    ledger->bank_totals[i] = calloc(4, sizeof(double));
  
  ledger->partition_totals = malloc(ledger->nbank * sizeof(double*));
  for(i = 0; i < ledger->nbank; ++i)
    ledger->partition_totals[i] = calloc(ledger->npartition[i], sizeof(double));
    
  for(i = 0; i < ledger->n; ++i){
    status = ledger->text_content[STATUS][i];
    amount = atof(ledger->text_content[AMOUNT][i]);

    k = -1;
    if(str_equal(status, CREDIT_NOT_THERE_YET)){
      k = 0;
    } else if(str_equal(status, CREDIT_PENDING)){
      k = 1;
    } else if(str_equal(status, CREDIT_CLEARED)){
      k = 2;
    } 

    if(k != -1)
      for(j = 0; j < ledger->ncredit; ++j) 
        if(str_equal(ledger->text_content[CREDIT][i], ledger->credit[j])){
          ledger->credit_totals[j][k] += amount;
          break;
        }
      
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) || 
       str_equal(status, NOT_THERE_YET)){
      k = 0;
    } else if(str_equal(status, PENDING)){
      k = 1;
    } else {
      k = 2;
    }
    
    for(j = 0; j < ledger->nbank; ++j){
      if(str_equal(ledger->text_content[BANK][i], ledger->bank[j])){
        ledger->bank_totals[j][k] += amount;

        for(k = 0; k < ledger->npartition[j]; ++k){
          if(str_equal(ledger->text_content[PARTITION][i], ledger->partition[j][k])){
            ledger->partition_totals[j][k] += amount;
            break;
          }
        } 

        break;
      }
    }
  }
  
  for(j = 0; j < ledger->ncredit; ++j)
    for(k = 0; k < 3; ++k)
      ledger->credit_totals[j][I_OVERALL] += ledger->credit_totals[j][k];

  for(j = 0; j < ledger->nbank; ++j)
    for(k = 0; k < 3; ++k){
      ledger->bank_totals[j][I_OVERALL] += ledger->bank_totals[j][k];
    }  
}
