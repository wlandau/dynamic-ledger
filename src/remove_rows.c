/***
 *** @file remove_rows.c
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
 
err_t remove_rows(Ledger *ledger, int *remove){
  int row, field, pos, i; 
  char tmp[ENTRYSIZE];

  if(ledger == NULL || remove == NULL)
    return LFAILURE;

  for(row = 0; row < ledger->nrows; ++row)
    if(remove[row]){
      pos = 0;
      for(i = row + 1; i < ledger->nrows; ++i)
        if(!remove[i]){
          pos = i;
          break;
        }
      
      if(pos){
        i = remove[row];
        remove[row] = remove[pos];
        remove[pos] = i;
      
        for(field = 0; field < NFIELDS; ++field){
          strcpy(tmp, ledger->entries[field][row]);
          strcpy(ledger->entries[field][row], ledger->entries[field][pos]);
          strcpy(ledger->entries[field][pos], tmp);
        }
      } else{
        break;
      }
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
