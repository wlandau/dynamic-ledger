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

int get_entries_from_stream(Ledger *ledger, FILE *fp){
  int i, row, field; 
  char c, line[LINESIZE];
  
  if(ledger == NULL)
    return 1;
  
  ledger->nrows = -1;
  while(fgets(line, LINESIZE, fp))
    ++ledger->nrows;
  
  if(ledger->nrows < 1){
    ledger->nrows = 1;
    alloc_entries(ledger);
    return 0;
  }
    
  rewind(fp);
  alloc_entries(ledger);
  
  field = 0;
  row = 0;
  i = 0;
  
  /* ignore the header */
  fgets(line, LINESIZE, fp);
  
  /* parse the data */
  while((c = fgetc(fp)) != EOF){

    if(c== '\t'){
      if(field < ENTRYSIZE){
        i = 0;
      }
      ++field; 
    } else if(c == '\n' || c == '\r'){
      if(field < ENTRYSIZE){
        i= 0;
      }
      field = 0;
      ++row; 
    } else if(field < NFIELDS && i < ENTRYSIZE - 1){
      ledger->entries[field][row][i] = c;
      ++i; 
    }
  }
  
  rewind(fp);
  return legal_amounts(ledger);
}
