/**
 * @file        print_ledger_to_string.c
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
 * @details Prints the ledger entries of a Ledger object
 *          to a character string in a format that can be 
 *          easily read back into a Ledger object
 *          by get_ledger.
 */
err_t print_ledger_to_string(Ledger *ledger, char **s){
  int field, row, n = 50;
  
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
      strncat(*s, "amount", ENTRYSIZE);
    else if(field == STATUS)
      strncat(*s, "status", ENTRYSIZE);
    else if(field == CREDIT)
      strncat(*s, "credit", ENTRYSIZE);
    else if(field == BANK)
      strncat(*s, "bank", ENTRYSIZE);
    else if(field == PARTITION)
      strncat(*s, "partition", ENTRYSIZE);
    else if(field == DESCRIPTION)
      strncat(*s, "description", ENTRYSIZE);
      
    if(field < NFIELDS - 1)
      strncat(*s, "\t", ENTRYSIZE);
    else
      strncat(*s, "\n", ENTRYSIZE);
  }  

  /* Print the actual ledger entries */
  
  for(row = 0; row < ledger->nrows; ++row){
    for(field = 0; field < NFIELDS - 1; ++field){
      strncat(*s, ledger->entries[field][row], ENTRYSIZE);
      strncat(*s, "\t", ENTRYSIZE);
    }
    strncat(*s, ledger->entries[NFIELDS - 1][row], ENTRYSIZE);
    strncat(*s, "\n", ENTRYSIZE);
  }

  /* Remove extra whitespace from the tail of the output string */
  
  if(str_strip(*s) == LFAILURE)
    return LFAILURE;
    
  return LSUCCESS;
}
