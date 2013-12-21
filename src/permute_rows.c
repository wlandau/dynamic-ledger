/**
 * @file        permute_rows.c
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
 * @details Permute the rows (transactions) of a Ledger object. 
 *          Specifically, bubble sort is applied to the int vector, 
 *          "order". The same sorting operations on "order" are 
 *          applied to the rows (transactions) of the Ledger object 
 *          in ledger->entries.
 */
err_t permute_rows(Ledger *ledger, int *order){
  int i, j, tmp, swapped;
  
  /* Check for NULL input */
  
  if(ledger == NULL || order == NULL)
    return LFAILURE;
    
  if(ledger->entries == NULL)
    return LFAILURE;
  
  if(ledger->nrows < 1)
    return LFAILURE;
  
  /* Use bubble sort (I expect the ledger to be almost already sorted). */
  
  for(i = 0; i < ledger->nrows; ++i){
    swapped = 0;
    for(j = ledger->nrows - 1; j > i; --j)
      if(order[j] < order[j - 1]){
        tmp = order[j - 1];
        order[j - 1] = order[j];
        order[j] = tmp;
      
        if(swap_rows(ledger, j - 1, j) == LFAILURE)
          return LFAILURE;
        swapped = 1;
      }
    if(!swapped)
      break;
  }
  
  return LSUCCESS;
}
