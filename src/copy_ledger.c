/**
 * @file        copy_ledger.c
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
 * @details Copies one Ledger object into another. Specifically,
 *          out_ledger is freed, and then in_ledger is copies into it.
 *          out_ledger should point to NULL if it is empty.
 */
err_t copy_ledger(Ledger **out_ledger, Ledger *in_ledger){
  int row, field;

  /* Check for null input */
  
  if(in_ledger == NULL)
    return LFAILURE;

  /* Allocate ledger to copy things into */

  free_ledger(out_ledger);
  
  if(new_ledger(out_ledger) == LFAILURE)
    return LFAILURE;
 
   /* Copy in_ledger into out_ledger */
  
  (*out_ledger)->nrows = in_ledger->nrows;
  
  if(alloc_entries(*out_ledger) == LFAILURE)
    return LFAILURE;
  
  for(field = 0; field < NFIELDS; ++field)
    for(row = 0; row < in_ledger->nrows; ++row)  
      strcpy((*out_ledger)->entries[field][row],
             in_ledger->entries[field][row]);
 
 /* Compute account names and summaries of out_ledger */
  
  if(get_names(*out_ledger) == LFAILURE)
    return LFAILURE;
    
  if(get_totals(*out_ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS; 
}

