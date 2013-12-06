/***
 *** @file summarize_file_to_stream.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int summarize_file_to_stream(const char* filename, FILE *fp){
  Ledger *ledger = get_ledger_from_filename(filename);
  int ind = (ledger == NULL);
  
  if(ind)
    return 1;

  print_summary_to_stream(ledger, fp);
  
  free_ledger(ledger);
  return 0;
}
