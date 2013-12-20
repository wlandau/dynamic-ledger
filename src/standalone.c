/***
 *** @file standalone.c
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

err_t standalone(int argc, char **argv){
  Ledger *ledger = NULL;

  if(argc == 2){

    if(get_ledger(&ledger, argv[1], NULL, NULL) == LFAILURE){
      print_summary_to_stream(ledger, stdout, USE_COLOR);
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(print_summary_to_stream(ledger, stdout, USE_COLOR) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(free_ledger(&ledger) == LFAILURE)
      return LFAILURE;

  } else if(argc == 3){

    if(get_ledger(&ledger, argv[1], NULL, NULL) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(clean(ledger, LNO) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(print_ledger_to_filename(ledger, argv[2]) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(free_ledger(&ledger) == LFAILURE)
      return LFAILURE;

  } else{
    if(usage() == LFAILURE)
      return LFAILURE; 
  }

  return LSUCCESS;
}
