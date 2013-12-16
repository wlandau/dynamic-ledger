/***
 *** @file filled_partitions.c
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

bool_t filled_partitions(Ledger *ledger, int bank){
  int i;
  bool_t ret = LNO;
 
  if(untotaled(ledger) == LYES)
    return LNO;

  for(i = 0; i < ledger->npartitions[bank]; ++i)
    if(fabs(ledger->partition_totals[bank][i]) > EPS){
      ret = LYES;
      break;
    }

  return ret;
}
