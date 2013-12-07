/***
 *** @file get_entries_from_string.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_entries_from_string(Ledger *ledger, char *s){
  int i, j, row, field;
  char c;
  
  if(ledger == NULL || s == NULL)
    return 1;

  ledger->nrows = 1;
  for(i = 0; i < strlen(s); ++i)
    if(s[i] == '\n' || s[i] == '\r')
      ++ledger->nrows;
      
  alloc_entries(ledger);

  field = 0;
  row = 0;
  j = 0;
  
  /* ignore header */
  for(i = 0; s[i] != '\n' && s[i] != '\r'; ++i);
  ++i;
  
  /* parse the data */
  for(; i < strlen(s); ++i){
    c = s[i];
      
    if(c== '\t'){
      if(field < ENTRYSIZE){
        j = 0;
      }
      ++field; 
    } else if(c == '\n' || c == '\r'){
      if(field < ENTRYSIZE){
        j = 0;
      }
      field = 0;
      ++row; 
    } else if(field < NFIELDS && j < ENTRYSIZE - 1){
      ledger->entries[field][row][j] = c;
      ++j;
    }
  } 
   
  return legal_amounts(ledger);
}
