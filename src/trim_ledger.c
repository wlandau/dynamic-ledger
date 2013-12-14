/***
 *** @file trim_ledger.c
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

err_t trim_ledger(Ledger *ledger){
  int row, field, pos, i; 
  char tmp[ENTRYSIZE];

  if(ledger == NULL)
    return LFAILURE;

  for(row = 0; row < ledger->nrows; ++row)
    if(abs(atof(ledger->entries[AMOUNT][row])) < EPS){
      pos = 0;
      for(i = row + 1; i < ledger->nrows; ++i)
        if(abs(atof(ledger->entries[AMOUNT][i])) >= EPS){
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
  
  for(field = 0; field < NFIELDS; ++field)
    for(i = row; i < ledger->nrows; ++i)
      free(ledger->entries[field][i]);
      
  ledger->nrows = row;
  return LSUCCESS;
}
