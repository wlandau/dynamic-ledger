/***
 *** @file filled_partitions.c
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

bool_t filled_partitions(Ledger *ledger, int bank){
  int i;
  bool_t ret = LNO;
 
  if(ledger == NULL) 
    return LFAILURE;
   
  if(ledger->nrows < 1 || bank < 0 || bank >= ledger->nbanks)
    return LFAILURE;  
 
  if(untotaled(ledger) == LYES)
    return LNO;

  for(i = 0; i < ledger->npartitions[bank]; ++i)
    if(small_norm(ledger->partition_totals[bank][i]) == LNO){
      ret = LYES;
      break;
    }

  return ret;
}
