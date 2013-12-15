/***
 *** @file permute_rows.c
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

err_t permute_rows(Ledger *ledger, int *order){
  int i, j, tmp, swapped;
  
  if(ledger == NULL || order == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
  
  if(ledger->nrows < 2)
    return LSUCCESS;
  
  /* bubble sort (I expect the ledger to be almost already sorted) */
  for(i = 0; i < ledger->nrows; ++i){
    swapped = 0;
    for(j = ledger->nrows - 1; j > i; --j)
      if(order[j] < order[j - 1]){
        tmp = order[j - 1];
        order[j - 1] = order[j];
        order[j] = tmp;
      
        swap_rows(ledger, j - 1, j);
        swapped = 1;
      }
    if(!swapped)
      break;
  }
  
  return LSUCCESS;
}
