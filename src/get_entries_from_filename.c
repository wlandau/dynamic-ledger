/**
 * @file        get_entries_from_filename.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Read the entries of a ledger from a filename
 *          into a Ledger object. This is really a wrapper
 *          around get_entries_from_stream. get_entries_from_filename
 *          mostly just opens the file and calls get_entries_from_stream.
 */
err_t get_entries_from_filename(Ledger *ledger, char *filename){
  err_t ret;
  FILE *fp = NULL;
  
  /*Check if input file name is good */
  
  if(input_file(filename) == LNO)
    return LFAILURE;
    
  if(strlen(filename) >= FILENAMESIZE)
    return LFAILURE;

  /* Open file and store file location in the Ledger object */
    
  fp = fopen(filename, "r");
  if(fp == NULL)
    return LFAILURE;
  
  if(ledger->filename == NULL)
    ledger->filename = malloc(FILENAMESIZE * sizeof(char));
  strcpy(ledger->filename, filename);
  
  /* Check if malloc worked */
  
  if(ledger->filename == NULL){
    fprintf(stderr, "Error: malloc failed\n");
    if(fp != NULL)
      fclose(fp);
    return LFAILURE;
  }
  
  /* Get the ledger entries from the file stream */
  
  ret = get_entries_from_stream(ledger, fp);

  /* Clean up and return */
    
  if(fp != NULL)
    fclose(fp);
  
  return ret;
}
