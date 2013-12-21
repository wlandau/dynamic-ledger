/**
 * @file        print_ledger_to_filename.c
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
 * @details Print the ledger entries of a Ledger object 
 *          to a file. This function is a wrapper around 
 *          print_ledger_to_stream. All it does is safely 
 *          open the file and then call print_ledger_to_stream.
 */
err_t print_ledger_to_filename(Ledger *ledger, char *filename){
  err_t ret;
  FILE *fp;
  
  /* Check for bad input */
  
  if(ledger == NULL || output_file(filename) == LNO)
    return LFAILURE;  

  /* Open the file and call print_ledger_to_stream */

  fp = fopen(filename, "w");
  ret = print_ledger_to_stream(ledger, fp);
  if(fp != NULL)
    fclose(fp);
    
  return ret;
}
