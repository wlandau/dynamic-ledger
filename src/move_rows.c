/***
 *** @file move_rows.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t move_rows(Ledger *ledger, int *rows, int nrows, int moveto){
  int i, *order;
  
  if(ledger == NULL || rows == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
    
  if(ledger->nrows < 2)
    return LSUCCESS;
  
  order = calloc(ledger->nrows, sizeof(int));
  qsort(rows, nrows, sizeof(int), icmp);
  
  for(i = moveto; i < ledger->nrows; ++i)
    order[i] = 2;
  
  for(i = 0; i < nrows; ++i)
    order[rows[i]] = 1;
  
  if(permute_rows(ledger, order) == LFAILURE){
    free(order);
    return LFAILURE;
  }
  
  free(order);
  return LSUCCESS;
}
