/***
 *** @file get_entries_from_stream.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t get_entries_from_filename(Ledger *ledger, char *filename){
  err_t ret;
  FILE *fp;
  
  if(input_file(filename) == LNO)
    return LFAILURE;
    
  fp = fopen(filename, "r");
  if(fp == NULL)
    return LFAILURE;
  
  ret = get_entries_from_stream(ledger, fp);
    
  if(fp != NULL)
    fclose(fp);
  
  return ret;
}
