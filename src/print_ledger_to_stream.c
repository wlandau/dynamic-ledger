/***
 *** @file print_ledger_to_stream.c
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

void print_ledger_to_stream(Ledger *ledger, FILE *fp){
  int row, field;
  
  if(ledger == NULL || fp == NULL)
    return;
  
  fprintf(fp, "amount\tstatus\tcredit\tbank\tpartition\tdescription\n");
  for(row = 0; row < ledger->nrows; ++row){
    for(field = 0; field < NFIELDS; ++field)
      fprintf(fp, "\t%s", ledger->entries[field][row]);
    fprintf(fp, "\n");
  }
}
