/***
 *** @file get_ledger_from_filename.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Ledger *get_ledger_from_filename(const char* filename){
  FILE *fp;
  Ledger *ledger = NULL;
  
  if(bad_input_file(filename))
    return NULL;
  
  fp = fopen(filename, "r");
  ledger = get_ledger_from_stream(fp); 
  fclose(fp);
  
  if(ledger == NULL)
    return NULL;
    
  ledger->filename = malloc(FILENAMESIZE * sizeof(char));
  strcpy(ledger->filename, filename);

  return ledger;
}
