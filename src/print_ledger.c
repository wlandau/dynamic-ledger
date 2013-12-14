/***
 *** @file print_ledger.c
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

err_t print_ledger(Ledger *in_ledger,  char *in_filename,            /* NEED TO IMPLEMENT ****/
  FILE *in_stream,  char *in_string, char *out_filename, 
  FILE *out_stream,  char **out_string){
  
  Ledger *ledger;
  
  if(in_ledger != NULL)
    ledger = in_ledger;
  else if(in_filename != NULL)
    get_ledger_from_filename(&ledger, in_filename);
  else if(in_stream != NULL)
    get_ledger_from_stream(&ledger, in_stream);
  else if(in_stream != NULL)
    get_ledger_from_string(&ledger, in_string);
  else
    return LFAILURE;  
    
  copy_ledger(&out_ledger, ledger);
  
  if(out_ledger != NULL)
    ledger = out_ledger;
  else if(in_filename != NULL)
    get_ledger_from_filename(&ledger, in_filename);
  else if(in_stream != NULL)
    get_ledger_from_stream(&ledger, in_stream);
  else if(in_stream != NULL)
    get_ledger_from_string(&ledger, in_string);
  else
    return LFAILURE;  
  
  
}
