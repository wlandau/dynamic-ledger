/**
 * @file        print_ledger_verbose.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Print all the information about a Ledger object
 *          to a file stream. This function is intended for
 *          debugging purposes only. The output is ugly.
 */
err_t print_ledger_verbose(Ledger *ledger, FILE *fp){
  int i, j, ret;;

  /* Check for bad input */

  if(ledger == NULL || fp == NULL)
    return LFAILURE;
    
  if(ledger->filename != NULL)
    fprintf(fp, "filename = %s.\n", ledger->filename);

  /* Print out entries and number of rows */
   
  fprintf(fp, "%d rows in data\n\n", ledger->nrows);
  
  ret = print_ledger_to_stream(ledger, fp);  
  if(ret == LFAILURE)
    return LFAILURE;  
    
  /* Print out calculated summaries */
    
  if(untotaled(ledger) == LYES)
    return LSUCCESS;
    
  fprintf(fp, "\n%d credit accounts:\n", ledger->ncredits);
  for(i = 0; i < ledger->ncredits; ++i){
    fprintf(fp, "\n  %s credit account:\n", ledger->credits[i]);
    fprintf(fp, "    %0.2f not arrived\n", ledger->credit_totals[i][I_NOT_THERE_YET]);
    fprintf(fp, "    %0.2f pending\n", ledger->credit_totals[i][I_PENDING]);
    fprintf(fp, "    %0.2f online balance\n", ledger->credit_totals[i][I_CLEARED]);
    fprintf(fp, "    %0.2f total\n", ledger->credit_totals[i][I_OVERALL_BAL]);
  }
  
  fprintf(fp, "\n%d bank accounts:\n", ledger->nbanks);
  for(i = 0; i < ledger->nbanks; ++i){
    fprintf(fp, "\n  %s bank account:\n", ledger->banks[i]);
    fprintf(fp, "    %0.2f\tnot arrived\n", ledger->bank_totals[i][I_NOT_THERE_YET]);
    fprintf(fp, "    %0.2f\tpending\n", ledger->bank_totals[i][I_PENDING]);
    fprintf(fp, "    %0.2f\tonline balance\n", ledger->bank_totals[i][I_CLEARED]);
    fprintf(fp, "    %0.2f\ttotal\n\n", ledger->bank_totals[i][I_OVERALL_BAL]);
    fprintf(fp, "    %d partitions\n", ledger->npartitions[i]);
    for(j = 0; j < ledger->npartitions[i]; ++j){
      if(strlen(ledger->partitions[i][j]))
        fprintf(fp, "      %0.2f\t%s\n", ledger->partition_totals[i][j],
                                        ledger->partitions[i][j]);
      else
        fprintf(fp, "      %0.2f\tunpartitioned\n", ledger->partition_totals[i][j]);
    }
  }  

  fprintf(fp, "\n");
  return LSUCCESS;
}
