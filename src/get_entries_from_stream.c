/**
 * @file        get_entries_from_stream.c
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
 * @details Get ledger entries from a file stream.
 *          This function first finds out how many
 *          rows there are in the input ledger and 
 *          the iterates over the file stream
 *          and parses characters individually with
 *          parse_char.
 */
err_t get_entries_from_stream(Ledger *ledger, FILE *fp){
  int char_index, row, field, nfail = 0; 
  char c, line[LINESIZE];
  err_t ret;
  
  /* Check for NULL input */
  
  if(ledger == NULL || fp == NULL)
    return LFAILURE;

  /* Get number of rows (transactions) */
  
  ledger->nrows = -1;
  while(fgets(line, LINESIZE, fp))
    ++ledger->nrows;
  
  if(ledger->nrows < 1){
    ledger->nrows = 0;
    return LSUCCESS;
  }
    
  rewind(fp);

  /* Allocate and read ledger entries */
  
  if(alloc_entries(ledger) == LFAILURE)
    return LFAILURE;
  
  field = 0;
  row = 0;
  char_index = 0;
  
  fgets(line, LINESIZE, fp);
  while((c = fgetc(fp)) != EOF)
    nfail += (parse_char(ledger, c, &char_index, &field, &row) == LFAILURE);
  rewind(fp);

  /* Strip leading and trailing whitespace from all the entries */
  
  ret = (strip_ledger(ledger) == LSUCCESS) && (!nfail);
  ret = ret && (legal_amounts(ledger) == LYES) && (legal_status_codes(ledger) == LYES);
  return ret ? LSUCCESS : LFAILURE;
}
