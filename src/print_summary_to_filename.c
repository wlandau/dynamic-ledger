/**
 * @file print_summary_to_filename.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Print a summary of a Ledger object to a file.
 *          This function is a wrapper around print_summary_to_stream.
 *          All it does is open the file and call
 *          print_summary_to_stream. Set usecolor to 1 to
 *          print with command line interface color codes 
 *          defined in the Printing_Macros module. Set usecolor to 0
 *          to not use these color codes.
 */
err_t print_summary_to_filename(Ledger *ledger, char *filename, int usecolor){
  err_t ret;
  FILE *fp;
  
  /* Check for bad input */
  
  if(ledger == NULL || output_file(filename) == LNO)
    return LFAILURE;

  /* Open the file and call print_summary_to_stream */

  fp = fopen(filename, "w");
  ret = print_summary_to_stream(ledger, fp, usecolor);
  if(fp != NULL)
    fclose(fp);
    
  return ret;
}
