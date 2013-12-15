/***
 *** @file swap_rows.c
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

err_t swap_rows(Ledger *ledger, int row1, int row2){
  int i;
  char tmp[ENTRYSIZE];
  
  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
    
  if(row1 < 0 || row1 >= ledger->nrows || row2 < 0 || row2 >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index.\n");
    return LFAILURE;
  }
  
  if(row1 == row2)
    return LSUCCESS;
    
  for(i = 0; i < NFIELDS; ++i){
    strcpy(tmp, ledger->entries[i][row1]);
    strcpy(ledger->entries[i][row1], ledger->entries[i][row2]);
    strcpy(ledger->entries[i][row2], tmp);  
  }
  
  return LSUCCESS;
}
