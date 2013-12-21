/**
 * @file        get_ledger.c
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
 * @details This function is the recommended way to
 *          read in a Ledger object from some source.
 *          It creates a new Ledger object, reads in the 
 *          entries from the specified source, and then
 *          calculates summary data on the ledger entries.
 *          To read from a filename, use the filename
 *          argument and set fp and str to NULL. To read from
 *          a file stream, use fp and set filename and str
 *          to NULL. To read from a string, use str and set
 *          filename and fp to NULL.
 */

err_t get_ledger(Ledger **ledger, char* filename, FILE *fp, char *str){
  int stat;
  
  /* Create a new ledger */
  
  if(new_ledger(ledger) == LFAILURE)
    return LFAILURE;

  /* Read in the ledger entries from the specified source */
  
  if(filename != NULL)
    stat = get_entries_from_filename(*ledger, filename);
  else if(fp != NULL)
    stat = get_entries_from_stream(*ledger, fp);
  else if(str != NULL)
    stat = get_entries_from_string(*ledger, str);
  else
    stat = LFAILURE;
  
  if(stat == LFAILURE)
    return LFAILURE;

  /* Compute and store summary data on the ledger entries */

  if(get_names(*ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(*ledger) == LFAILURE)
    return LFAILURE;
    
  return LSUCCESS;
}
