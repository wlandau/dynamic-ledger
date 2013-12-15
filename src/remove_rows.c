/***
 *** @file remove_rows.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t remove_rows(Ledger *ledger){
  int row, field, pos, i; 
  char tmp[ENTRYSIZE];

  if(ledger == NULL)
    return LFAILURE;

  for(row = 0; row < ledger->nrows; ++row)
    if(str_equal(ledger->entries[STATUS][row], REMOVE)){
      pos = 0;
      for(i = row + 1; i < ledger->nrows; ++i)
        if(!str_equal(ledger->entries[STATUS][i], REMOVE)){
          pos = i;
          break;
        }
      
      if(pos){
        for(field = 0; field < NFIELDS; ++field){
          strcpy(tmp, ledger->entries[field][row]);
          strcpy(ledger->entries[field][row], ledger->entries[field][pos]);
          strcpy(ledger->entries[field][pos], tmp);
        }
      } else{
        break;
      }
    }
  
  if(!row){
    fprintf(stderr, "Warning: cannot remove all rows. Leaving one blank row instead.\n");
    for(field = 0; field < NFIELDS; ++field)
      strcpy(ledger->entries[field][0], NIL);
    ++row;
  }
  
  for(field = 0; field < NFIELDS; ++field)
    for(i = row; i < ledger->nrows; ++i)
      free(ledger->entries[field][i]);
  ledger->nrows = row;
  
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);
  return LSUCCESS;
}
