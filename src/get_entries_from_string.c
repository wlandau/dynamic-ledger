/***
 *** @file get_entries_from_string.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t get_entries_from_string(Ledger *ledger, char *s){
  int i, char_index, field, row, nfail = 0;
  err_t ret;
  
  if(ledger == NULL || s == NULL)
    return LFAILURE;

  ledger->nrows = 1;
  for(i = 0; i < strlen(s); ++i)
    if(row_delim_char(s[i]) == LYES)
      ++ledger->nrows;
      
  if(alloc_entries(ledger) == LFAILURE)
    return LFAILURE;

  for(i = 0; i < strlen(s) && row_delim_char(s[i]) == LNO; ++i);
  ++i;
  
  char_index = 0;
  field = 0;
  row = 0;
  for(; i < strlen(s); ++i)
    nfail += (parse_char(ledger, s[i], &char_index, &field, &row) == LFAILURE);
    
  ret = (strip_ledger(ledger) == LSUCCESS) && (!nfail);
  ret = ret && (legal_amounts(ledger) == LYES) && (legal_status_codes(ledger) == LYES);
  return ret ? LSUCCESS : LFAILURE;
}
