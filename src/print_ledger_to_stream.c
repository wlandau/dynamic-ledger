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

err_t print_ledger_to_stream(Ledger *ledger, FILE *fp){
  int row, field;
  
  if(ledger == NULL || fp == NULL)
    return LFAILURE;

  for(field = 0; field < NFIELDS; ++field){
    if(field == AMOUNT)
      fprintf(fp, "amount");
    else if(field == STATUS)
      fprintf(fp, "status");
    else if(field == CREDIT)
      fprintf(fp, "credit");
    else if(field == BANK)
      fprintf(fp, "bank");
    else if(field == PARTITION)
      fprintf(fp, "partition");
    else if(field == DESCRIPTION)
      fprintf(fp, "description");
      
    if(field < NFIELDS - 1)
      fprintf(fp, "\t");
    else
      fprintf(fp, "\n");
  }

  for(row = 0; row < ledger->nrows; ++row){
    for(field = 0; field < NFIELDS - 1; ++field)
      fprintf(fp, "%s\t", ledger->entries[field][row]);
    fprintf(fp, "%s\n", ledger->entries[NFIELDS - 1][row]);
  }
  
  return LSUCCESS;
}
