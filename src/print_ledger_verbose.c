/***
 *** @file print_ledger_verbose.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_ledger_verbose(Ledger *ledger, FILE *fp){
  int i, j;

  if(ledger == NULL || fp == NULL)
    return;
    
  if(ledger->filename != NULL)
    fprintf(fp, "filename = %s.\n", ledger->filename);
   
  fprintf(fp, "%d rows in data\n\n", ledger->n);  
    
  fprintf(fp, "%d credit accounts:\n", ledger->ncredit);
  for(i = 0; i < ledger->ncredit; ++i){
    fprintf(fp, "\n  %s credit account:\n", ledger->credit[i]);
    fprintf(fp, "    %0.2f not arrived\n", ledger->credit_totals[i][I_NOT_THERE_YET]);
    fprintf(fp, "    %0.2f pending\n", ledger->credit_totals[i][I_PENDING]);
    fprintf(fp, "    %0.2f online balance\n", ledger->credit_totals[i][I_CLEARED]);
    fprintf(fp, "    %0.2f total\n", ledger->credit_totals[i][I_OVERALL]);
  }
  
  fprintf(fp, "\n%d bank accounts:\n", ledger->nbank);
  for(i = 0; i < ledger->nbank; ++i){
    fprintf(fp, "\n  %s bank account:\n", ledger->bank[i]);
    fprintf(fp, "    %0.2f\tnot arrived\n", ledger->bank_totals[i][I_NOT_THERE_YET]);
    fprintf(fp, "    %0.2f\tpending\n", ledger->bank_totals[i][I_PENDING]);
    fprintf(fp, "    %0.2f\tonline balance\n", ledger->bank_totals[i][I_CLEARED]);
    fprintf(fp, "    %0.2f\ttotal\n\n", ledger->bank_totals[i][I_OVERALL]);
    fprintf(fp, "    %d partitions\n", ledger->npartition[i]);
    for(j = 0; j < ledger->npartition[i]; ++j){
      if(strlen(ledger->partition[i][j]))
        fprintf(fp, "      %0.2f\t%s\n", ledger->partition_totals[i][j],
                                        ledger->partition[i][j]);
      else
        fprintf(fp, "      %0.2f\tunpartitioned\n", ledger->partition_totals[i][j]);
    }
  }  

  fprintf(fp, "\n");
  print_ledger_to_stream(ledger, fp);
}
