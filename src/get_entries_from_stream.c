/***
 *** @file get_entries_from_stream.c
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

err_t get_entries_from_stream(Ledger *ledger, FILE *fp){
  int char_index, row, field; 
  char c, line[LINESIZE];
  
  if(ledger == NULL || fp == NULL)
    return LFAILURE;
  
  ledger->nrows = -1;
  while(fgets(line, LINESIZE, fp))
    ++ledger->nrows;
  
  if(ledger->nrows < 1){
    ledger->nrows = 1;
    alloc_entries(ledger);
    return LSUCCESS;
  }
    
  rewind(fp);
  
  if(alloc_entries(ledger) == LFAILURE)
    return LFAILURE;
  
  field = 0;
  row = 0;
  char_index = 0;
  
  fgets(line, LINESIZE, fp);
  while((c = fgetc(fp)) != EOF)
    parse_char(ledger, c, &char_index, &field, &row);
  
  rewind(fp);
  return legal_amounts(ledger) && legal_status_codes(ledger) ? LSUCCESS : LFAILURE;
}
