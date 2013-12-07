/***
 *** @file print_ledger_to_stream.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_ledger_to_stream(Ledger *ledger, FILE *fp){
  int i, j;
  double amount;
  
  if(ledger == NULL || fp == NULL)
    return;
  
  fprintf(fp, "amount\tstatus\tcredit\tbank\tpartition\tdescription\n");
  for(i = 0; i < ledger->nrows; ++i){
    amount = atof(ledger->entries[AMOUNT][i]);
    fprintf(fp, "%0.2f", amount);
    for(j = 1; j < NFIELDS; ++j)
      fprintf(fp, "\t%s", ledger->entries[j][i]);
    fprintf(fp, "\n");
  }
}
