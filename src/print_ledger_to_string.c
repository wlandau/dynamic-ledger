/**
 * @file        print_ledger_to_string.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Prints the ledger entries of a Ledger object
 *          to a character string in a format that can be 
 *          easily read back into a Ledger object
 *          by get_ledger.
 */
err_t print_ledger_to_string(Ledger *ledger, char **s){
  int field, row, n = 1;
  
  /* Check for bad input */
  
  if(ledger == NULL)
    return LFAILURE;

  /* Remove leading and trailing whitespace from the entries */

  if(strip_ledger(ledger) == LFAILURE)
    return LFAILURE;

  /* Allocate space for the output string and check that malloc worked */
  
  for(field = 0; field < NFIELDS; ++field)  
    for(row = 0; row < ledger->nrows; ++row)
      n += strlen(ledger->entries[field][row]) + 1;
  
  *s = calloc(n + LINESIZE, sizeof(char));
  if(*s == NULL){
    fprintf(stderr, "Error: malloc failed.\n");
    return LFAILURE;
  }

  /* Print the header */
  
  for(field = 0; field < NFIELDS; ++field){
    if(field == AMOUNT)
      strcat(*s, "amount");
    else if(field == STATUS)
      strcat(*s, "status");
    else if(field == CREDIT)
      strcat(*s, "credit");
    else if(field == BANK)
      strcat(*s, "bank");
    else if(field == PARTITION)
      strcat(*s, "partition");
    else if(field == DESCRIPTION)
      strcat(*s, "description");
      
    if(field < NFIELDS - 1)
      strcat(*s, "\t");
    else
      strcat(*s, "\n");
  }  

  /* Print the actual ledger entries */
  
  for(row = 0; row < ledger->nrows; ++row){
    for(field = 0; field < NFIELDS - 1; ++field){
      strcat(*s, ledger->entries[field][row]);
      strcat(*s, "\t");
    }
    strcat(*s, ledger->entries[NFIELDS - 1][row]);
    strcat(*s, "\n");
  }

  /* Remove extra whitespace from the tail of the output string */
  
  if(str_strip(*s) == LFAILURE)
    return LFAILURE;
    
  return LSUCCESS;
}
