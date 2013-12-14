/***
 *** @file condense_and_print.c
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
int condense_and_print(char* infile, char *outfile){
  FILE *fp;
  Ledger *ledger;
  
  if(input_file(infile) == LNO)
    return 1;
  
  get_ledger(&ledger, infile, NULL, NULL);
  if(ledger == NULL){
    fprintf(stderr, "Failed to read ledger.\n");
    return 1;
  }  
  
  condense(&ledger);
      
  if(output_file(outfile) == LYES){
    fp = fopen(outfile, "w");
    print_ledger_to_stream(ledger, fp);
    fclose(fp);
  }
  
  free_ledger(ledger);
  return 0;
}
