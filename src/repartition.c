/***
 *** @file insert_row.c
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

err_t repartition(Ledger *ledger, char *bank, char **partitions, 
                  double *amounts, int npartitions, int as_percentages){
  
  int i, row, ibank, oldnrows;
  double sum;
  
  if(ledger == NULL || npartitions < 1)
    return LFAILURE;

  ibank = which(ledger->banks, bank, ledger->nbanks);

  if(ibank == NO_INDEX)
    return LFAILURE;
    
  if(as_percentages)
    for(i = 0; i < npartitions; ++i)
      amounts[i] *= ledger->bank_totals[ibank][I_OVERALL_BAL] / 100.0;

  sum = 0;
  for(i = 0; i < npartitions; ++i)  
    sum += amounts[i];

  if((sum - ledger->bank_totals[ibank][I_OVERALL_BAL]) > EPS){
    fprintf(stderr, "Error: your partition totals sum to %0.2f.\n", sum);
    fprintf(stderr, "They should sum to the true total balance, %0.2f,\n", 
            ledger->bank_totals[ibank][I_OVERALL_BAL]); 
    fprintf(stderr, "of bank account \"%s\".\n", bank);
    return LFAILURE; 
  }
  
  oldnrows = ledger->nrows;
  if(insert_rows(ledger, ledger->nrows, ledger->npartitions[ibank] + npartitions) == LFAILURE)
    return LFAILURE;
    
  for(i = 0; i < ledger->npartitions[ibank]; ++i){
    row = i + oldnrows;
    sprintf(ledger->entries[AMOUNT][row], "%0.2f", -ledger->partition_totals[ibank][i]);
    strcpy(ledger->entries[PARTITION][row], ledger->partitions[ibank][i]);
    strcpy(ledger->entries[BANK][row], bank);
    strcpy(ledger->entries[DESCRIPTION][row], "repartition");
  }
  
  for(i = 0; i < npartitions; ++i){
    row = i + oldnrows + ledger->npartitions[ibank];
    sprintf(ledger->entries[AMOUNT][row], "%0.2f", amounts[i]);    
    strcpy(ledger->entries[PARTITION][row], partitions[i]); 
    strcpy(ledger->entries[BANK][row], bank);       
    strcpy(ledger->entries[DESCRIPTION][row], "repartition");    
  }
  
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);    
  return LSUCCESS;
}
