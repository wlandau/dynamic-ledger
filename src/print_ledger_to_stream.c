/**
 * @file        print_ledger_to_stream.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License >= 3.0 (See COPYING.txt)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Prints the ledger entries of a Ledger object
 *          to a file stream in a format that can be 
 *          easily read back into a Ledger object
 *          by get_ledger.
 */
err_t print_ledger_to_stream(Ledger *ledger, FILE *fp){
  int row, field;
  
  /* Check for bad input */
  
  if(ledger == NULL || fp == NULL)
    return LFAILURE;

  /* Remove leading and trailing whitespace from the entries */

  if(strip_ledger(ledger) == LFAILURE)
    return LFAILURE;

  /* Print the header */

  for(field = 0; field < NFIELDS; ++field){
    if(field == AMOUNT)
      fprintf(fp, "amount");
    else if(field == STATUS)
      fprintf(fp, "status");
    else if(field == CREDIT)
      fprintf(fp, "credit");
    else if(field == BANK)
      fprintf(fp, "bank");
    else if(field == PARTITION)
      fprintf(fp, "partition");
    else if(field == DESCRIPTION)
      fprintf(fp, "description");
      
    if(field < NFIELDS - 1)
      fprintf(fp, "\t");
    else
      fprintf(fp, "\n");
  }

  /* Print the actual ledger entries */

  if(ledger->entries != NULL)
    for(row = 0; row < ledger->nrows; ++row){
      for(field = 0; field < NFIELDS - 1; ++field)
        fprintf(fp, "%s\t", ledger->entries[field][row]);
      fprintf(fp, "%s\n", ledger->entries[NFIELDS - 1][row]);
    }
  
  return LSUCCESS;
}
