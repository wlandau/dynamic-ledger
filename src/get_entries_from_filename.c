/***
 *** @file get_entries_from_filename.c
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

err_t get_entries_from_filename(Ledger *ledger, char *filename){
  err_t ret;
  FILE *fp = NULL;
  
  /* CHECK IF INPUT FILE NAME IS GOOD */
  
  if(input_file(filename) == LNO)
    return LFAILURE;

  /* OPEN FILE AND STORE FILE NAME */
    
  fp = fopen(filename, "r");
  if(fp == NULL)
    return LFAILURE;
  
  if(ledger->filename == NULL)
    ledger->filename = malloc(FILENAMESIZE * sizeof(char));
  strcpy(ledger->filename, filename);
  
  /* CHECK IF MALLOC WORKED */
  
  if(ledger->filename == NULL){
    fprintf(stderr, "Error: malloc failed\n");
    if(fp != NULL)
      fclose(fp);
    return LFAILURE;
  }
  
  /* GET THE LEDGER ENTRIES FROM THE FILE STREAM */
  
  ret = get_entries_from_stream(ledger, fp);

  /* CLEAN UP AND EXIT */
    
  if(fp != NULL)
    fclose(fp);
  
  return ret;
}
