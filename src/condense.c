/***
 *** @file condense.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void condense(Ledger **ledger){
  int i, j, k, new_n, row = 0;
  double **local_partition_totals;
  char status[ENTRYSIZE], amount[ENTRYSIZE];
  Ledger *newledger, *tmpledger;
  
  if(ledger == NULL || *ledger == NULL)
    return;

  local_partition_totals = malloc((*ledger)->nbank * sizeof(double*));
  for(i = 0; i < (*ledger)->nbank; ++i){
    local_partition_totals[i] = calloc((*ledger)->npartition[i], sizeof(double));  
    for(j = 0; j < (*ledger)->npartition[i]; ++j)
      local_partition_totals[i][j] = (*ledger)->partition_totals[i][j];
  }

  for(i = 0; i < (*ledger)->n; ++i){
    strcpy(status, (*ledger)->text_content[STATUS][i]);
    strcpy(amount, (*ledger)->text_content[AMOUNT][i]);
  
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOT_THERE_YET) || 
       str_equal(status, PENDING) ||
       str_equal(status, LOCKED)){ 

      for(j = 0; j < (*ledger)->nbank; ++j)
        if(str_equal((*ledger)->text_content[BANK][i], (*ledger)->bank[j])){
         for(k = 0; k < (*ledger)->npartition[j]; ++k){
            if(str_equal((*ledger)->text_content[PARTITION][i], (*ledger)->partition[j][k])){
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
  for(i = 0; i < (*ledger)->n; ++i)
    new_n += (strlen((*ledger)->text_content[STATUS][i]) > 0);

  for(i = 0; i < (*ledger)->nbank; ++i)
    new_n += (*ledger)->npartition[i];

  newledger->n = new_n;
  alloc_text_content(newledger);  
  
  for(i = 0; i < (*ledger)->n; ++i){
    strcpy(status, (*ledger)->text_content[STATUS][i]);
    strcpy(amount, (*ledger)->text_content[AMOUNT][i]);
  
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOT_THERE_YET) || 
       str_equal(status, PENDING) || 
       str_equal(status, LOCKED)){ 
      
      if(abs(atof(amount)) > EPS){
        for(j = 0; j < NFIELDS; ++j)
          strcpy(newledger->text_content[j][row], (*ledger)->text_content[j][i]);
        ++row;
      }
    }
  } 
   
  for(i = 0; i < (*ledger)->nbank; ++i)
    for(j = 0; j < (*ledger)->npartition[i]; ++j)
      if(abs(local_partition_totals[i][j]) > EPS){
        sprintf(amount, "%0.2f", local_partition_totals[i][j]);
        strcpy(newledger->text_content[AMOUNT][row], amount);
        strcpy(newledger->text_content[BANK][row], (*ledger)->bank[i]);
        strcpy(newledger->text_content[PARTITION][row], (*ledger)->partition[i][j]);
        strcpy(newledger->text_content[DESCRIPTION][row], "condensed");
        ++row;
      }

  for(i = 0; i < (*ledger)->nbank; ++i)
    free(local_partition_totals[i]);  
  free(local_partition_totals); 

  get_names(newledger);
  get_totals(newledger); 
  trim_ledger(newledger); 
  
  tmpledger = *ledger;
  *ledger = newledger;
  free_ledger(tmpledger); 
}
