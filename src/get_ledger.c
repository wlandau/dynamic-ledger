/***
 *** @file get_ledger.c
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

err_t get_ledger(Ledger **ledger, char* filename, FILE *fp, char *str){
  int stat;
  new_ledger(ledger);
  
  if(filename != NULL)
    stat = get_entries_from_filename(*ledger, filename);
  else if(fp != NULL)
    stat = get_entries_from_stream(*ledger, fp);
  else if(str != NULL)
    stat = get_entries_from_string(*ledger, str);
  else
    stat = LFAILURE;
  
  if(stat == LFAILURE)
    return LFAILURE;

  if(get_names(*ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(*ledger) == LFAILURE)
    return LFAILURE;
    
  return LSUCCESS;
}
