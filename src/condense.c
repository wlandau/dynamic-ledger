/***
 *** @file condense.c
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

void condense(Ledger **ledger){
  int i, j, k, new_n, row = 0;
  double **local_partition_totals;
  char status[ENTRYSIZE], amount[ENTRYSIZE];
  Ledger *newledger, *tmpledger;
  
  if(ledger == NULL || *ledger == NULL)
    return;

  local_partition_totals = malloc((*ledger)->nbanks * sizeof(double*));
  for(i = 0; i < (*ledger)->nbanks; ++i){
    local_partition_totals[i] = calloc((*ledger)->npartitions[i], sizeof(double));  
    for(j = 0; j < (*ledger)->npartitions[i]; ++j)
      local_partition_totals[i][j] = (*ledger)->partition_totals[i][j];
  }

  for(i = 0; i < (*ledger)->nrows; ++i){
    strcpy(status, (*ledger)->entries[STATUS][i]);
    strcpy(amount, (*ledger)->entries[AMOUNT][i]);
  
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOT_THERE_YET) || 
       str_equal(status, PENDING) ||
       str_equal(status, LOCKED)){ 

      for(j = 0; j < (*ledger)->nbanks; ++j)
        if(str_equal((*ledger)->entries[BANK][i], (*ledger)->banks[j])){
         for(k = 0; k < (*ledger)->npartitions[j]; ++k){
            if(str_equal((*ledger)->entries[PARTITION][i], (*ledger)->partitions[j][k])){
              local_partition_totals[j][k] -= atof(amount);
              
              break;
            } 
          }
          break;
        }
    }
  } 
    
  newledger = malloc(sizeof(Ledger));
  newledger->filename = NULL;
  
  new_n = 0;
  for(i = 0; i < (*ledger)->nrows; ++i)
    new_n += (strlen((*ledger)->entries[STATUS][i]) > 0);

  for(i = 0; i < (*ledger)->nbanks; ++i)
    new_n += (*ledger)->npartitions[i];

  newledger->nrows = new_n;
  alloc_entries(newledger);  
  
  for(i = 0; i < (*ledger)->nrows; ++i){
    strcpy(status, (*ledger)->entries[STATUS][i]);
    strcpy(amount, (*ledger)->entries[AMOUNT][i]);
  
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOT_THERE_YET) || 
       str_equal(status, PENDING) || 
       str_equal(status, LOCKED)){ 
      
      if(abs(atof(amount)) > EPS){
        for(j = 0; j < NFIELDS; ++j)
          strcpy(newledger->entries[j][row], (*ledger)->entries[j][i]);
        ++row;
      }
    }
  } 
   
  for(i = 0; i < (*ledger)->nbanks; ++i)
    for(j = 0; j < (*ledger)->npartitions[i]; ++j)
      if(abs(local_partition_totals[i][j]) > EPS){
        sprintf(amount, "%0.2f", local_partition_totals[i][j]);
        strcpy(newledger->entries[AMOUNT][row], amount);
        strcpy(newledger->entries[BANK][row], (*ledger)->banks[i]);
        strcpy(newledger->entries[PARTITION][row], (*ledger)->partitions[i][j]);
        strcpy(newledger->entries[DESCRIPTION][row], "condensed");
        ++row;
      }

  for(i = 0; i < (*ledger)->nbanks; ++i)
    free(local_partition_totals[i]);  
  free(local_partition_totals); 

  get_names(newledger);
  get_totals(newledger); 
  trim_ledger(newledger); 
  
  tmpledger = *ledger;
  *ledger = newledger;
  free_ledger(tmpledger); 
}
