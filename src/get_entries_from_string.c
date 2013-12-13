/***
 *** @file get_entries_from_string.c
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

err_t get_entries_from_string(Ledger *ledger, char *s){
  int i, char_index, field, row;
  
  if(ledger == NULL || s == NULL)
    return LFAILURE;

  ledger->nrows = 1;
  for(i = 0; i < strlen(s); ++i)
    if(row_delim_char(s[i]) == LYES)
      ++ledger->nrows;
      
  alloc_entries(ledger);

  for(i = 0; row_delim_char(s[i]) == LNO; ++i);
  ++i;
  
  char_index = 0;
  field = 0;
  row = 0;
  for(; i < strlen(s); ++i)
    parse_char(ledger, s[i], &char_index, &field, &row);
   
  return legal_amounts(ledger) && legal_status_codes(ledger) ? LSUCCESS : LFAILURE;
}
