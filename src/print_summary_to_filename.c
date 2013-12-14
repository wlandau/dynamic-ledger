/***
 *** @file print_summary_to_filename.c
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

err_t print_summary_to_filename(Ledger *ledger, char *filename){
  err_t ret;
  FILE *fp;
  
  if(ledger == NULL || output_file(filename) == LNO)
    return LFAILURE;

  fp = fopen(filename, "w");
  ret = print_summary_to_stream(ledger, fp);
  if(fp != NULL)
    fclose(fp);
    
  return ret;
}
