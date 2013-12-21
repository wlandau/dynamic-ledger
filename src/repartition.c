/**
 * @file        repartition.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */
 
#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Repartition a bank account, allocating amounts_arg[i] of money
 *          to partition partitions[i] (i = 0, ..., npartitions - 1).
 *          Set as_percentages to 1 to interpret the elements of amounts_arg
 *          as percentages, in which case the sum of the entries of amounts_arg
 *          must equal 100. Set as_percentages to 0 otherwise, in which case 
 *          the sum of the entries of amounts_arg must equal the overall true
 *          balance of the given bank account.
 */

err_t repartition(Ledger *ledger, char *bank, char **partitions, 
                  double *amounts_arg, int npartitions, int as_percentages){
  
  int i, row, ibank, oldnrows;
  double sum, *amounts;
  
  /* Check for NULL input */
  
  if(ledger == NULL || bank == NULL || partitions == NULL || 
     amounts_arg == NULL || npartitions < 1)
    return LFAILURE;
  
  if(ledger->nrows < 1)
    return LFAILURE;
    
  if(untotaled(ledger) == LYES)
    return LFAILURE;

  ibank = which(ledger->banks, bank, ledger->nbanks);

  if(ibank == NO_INDEX)
    return LFAILURE;
    
  /* Allocate space for new amounts and check if malloc worked */
    
  amounts = malloc(npartitions * sizeof(double));
  for(i = 0; i < npartitions; ++i)
    amounts[i] = amounts_arg[i]; 
    
  if(amounts == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }     
    
  /* Check if proposed partition totals sum to the correct bank total */  
    
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
 
  /* Do the repartitioning by inserting new rows */  
  
  oldnrows = ledger->nrows;
  if(insert_rows(ledger, ledger->nrows, 
                 ledger->npartitions[ibank] + npartitions) == LFAILURE){
    free(amounts);
    return LFAILURE;
  }
    
  /* Insert rows to set the totals of the old partitions to 0 */  
    
  for(i = 0; i < ledger->npartitions[ibank]; ++i){
    row = i + oldnrows;
    sprintf(ledger->entries[AMOUNT][row], "%0.2f", -ledger->partition_totals[ibank][i]);
    strcpy(ledger->entries[PARTITION][row], ledger->partitions[ibank][i]);
    strcpy(ledger->entries[BANK][row], bank);
    strcpy(ledger->entries[DESCRIPTION][row], "repartition");
  }
  
  /* Insert new rows giving the new partition totals */  
  
  for(i = 0; i < npartitions; ++i){
    row = i + oldnrows + ledger->npartitions[ibank];
    sprintf(ledger->entries[AMOUNT][row], "%0.2f", amounts[i]);    
    strcpy(ledger->entries[PARTITION][row], partitions[i]); 
    strcpy(ledger->entries[BANK][row], bank);       
    strcpy(ledger->entries[DESCRIPTION][row], "repartition");    
  }

  /* Update the Ledger object to reflect the changes */
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_names(ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(ledger) == LFAILURE)
    return LFAILURE; 
 
  /* Clean up and return */
 
  free(amounts);    
  return LSUCCESS;
}
