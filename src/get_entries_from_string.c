/**
 * @file        get_entries_from_string.c
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
 * @details Get ledger entries from a string.
 *          This function first finds out how many
 *          rows there are in the input ledger and 
 *          the iterates over the string
 *          and parses characters individually with
 *          parse_char.
 */
err_t get_entries_from_string(Ledger *ledger, char *s){
  int i, char_index, field, row, nfail = 0;
  err_t ret;
  
  /* Check for NULL input */
  
  if(ledger == NULL || s == NULL)
    return LFAILURE;

  /* Get number of rows (transactions) */

  ledger->nrows = 0;
  for(i = 0; i < strlen(s); ++i)
    if(row_delim_char(s[i]) == LYES)
      ++ledger->nrows;
   
  if(!ledger->nrows)
    return LFAILURE;   

  /* Allocate and read ledger entries */
      
  if(alloc_entries(ledger) == LFAILURE)
    return LFAILURE;

  for(i = 0; i < strlen(s) && row_delim_char(s[i]) == LNO; ++i);
  ++i;
  
  char_index = 0;
  field = 0;
  row = 0;
  for(; i < strlen(s); ++i)
    nfail += (parse_char(ledger, s[i], &char_index, &field, &row) == LFAILURE);

  /* Strip leading and trailing whitespace from all the entries */
    
  ret = (strip_ledger(ledger) == LSUCCESS) && (!nfail);
  ret = ret && (legal_amounts(ledger) == LYES) && (legal_status_codes(ledger) == LYES);
  return ret ? LSUCCESS : LFAILURE;
}
