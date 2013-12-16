/***
 *** @file clean.c
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

err_t clean(Ledger *ledger, int sort_locked){
  
  if(condense(ledger) == LFAILURE){
    fprintf(stderr, "Error: could not condense ledger.\n");
    return LFAILURE;
  }

  if(sort_by_status(ledger, sort_locked) == LFAILURE){
    fprintf(stderr, "Error: could not sort transactions by status.\n");
    return LFAILURE;
  }
 
  return LSUCCESS;
}
