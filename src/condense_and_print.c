/***
 *** @file condense_and_print.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int condense_and_print(const char* infile, const char *outfile){
  FILE *fp;
  Ledger *ledger;
  
  if(bad_input_file(infile))
    return 1;
  
  ledger = get_ledger_from_filename(infile);
  if(ledger == NULL){
    printf("Failed to read ledger.\n");
    return 1;
  }  
  
  condense(&ledger);
      
  if(!bad_output_file(outfile)){
    fp = fopen(outfile, "w");
    print_ledger_to_stream(ledger, fp);
    fclose(fp);
  }
  
  free_ledger(ledger);
  return 0;
}
