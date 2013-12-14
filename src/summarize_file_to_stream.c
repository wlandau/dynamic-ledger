/***
 *** @file summarize_file_to_stream.c
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

int summarize_file_to_stream(char* filename, FILE *fp){
  Ledger *ledger;
  get_ledger(&ledger, filename, NULL, NULL);
  
  if(ledger == NULL)
    return 1;

  print_summary_to_stream(ledger, fp, 1);
  
  free_ledger(&ledger);
  return 0;
}
