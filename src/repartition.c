/***
 *** @file repartition.c
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

err_t repartition(Ledger *ledger, char *bank, char **partitions, 
                  double *amounts_arg, int npartitions, int as_percentages){
  
  int i, row, ibank, oldnrows;
  double sum, *amounts;
  
  /* CHECK FOR NULL INPUT */
  
  if(ledger == NULL || bank == NULL || partitions == NULL || 
     amounts_arg == NULL || npartitions < 1)
    return LFAILURE;
    
  if(untotaled(ledger) == LYES)
    return LFAILURE;

  ibank = which(ledger->banks, bank, ledger->nbanks);

  if(ibank == NO_INDEX)
    return LFAILURE;
    
  /* ALLOCATE SPACE FOR NEW AMOUNTS AND CHECK IF MALLOC WORKED */
    
  amounts = malloc(npartitions * sizeof(double));
  for(i = 0; i < npartitions; ++i)
    amounts[i] = amounts_arg[i]; 
    
  if(amounts == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }     
    
  /* CHECK IF PROPOSED PARTITION TOTALS SUM TO THE CORRECT BANK TOTAL */  
    
  if(as_percentages)
    for(i = 0; i < npartitions; ++i)
      amounts[i] *= ledger->bank_totals[ibank][I_OVERALL_BAL] / 100.0;

  sum = 0;
  for(i = 0; i < npartitions; ++i)  
    sum += amounts[i];

  if(small_norm(sum - ledger->bank_totals[ibank][I_OVERALL_BAL]) == LNO){
    fprintf(stderr, "Error: your partition totals sum to %0.2f.\n", sum);
    fprintf(stderr, "They should sum to the true total balance, %0.2f,\n", 
            ledger->bank_totals[ibank][I_OVERALL_BAL]); 
    fprintf(stderr, "of bank account \"%s\".\n", bank);
    free(amounts);
    return LFAILURE; 
  }
 
  /* DO THE REPARTITIONING BY INSERTING NEW ROWS */  
  
  oldnrows = ledger->nrows;
  if(insert_rows(ledger, ledger->nrows, 
                 ledger->npartitions[ibank] + npartitions) == LFAILURE){
    free(amounts);
    return LFAILURE;
  }
    
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

  /* RECALCULATE NAMES AND TOTALS */
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
 
  /* CLEAN UP AND EXIT */
 
  free(amounts);    
  return LSUCCESS;
}
