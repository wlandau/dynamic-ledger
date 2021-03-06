/**
 * @file        which_bank_total.c
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
 * @details Given a status code, this function finds the correct index in 
 *          the bank_totals array member of the Ledger type. bank_totals
 *          is an array indexed by the transaction status given in the
 *          Status_Macros module. If no index is found for the given
 *          status code, NO_INDEX is returned.
 */
index_t which_bank_total(char *status){
  if(status == NULL)
    return NO_INDEX;
    
  if(str_equal(status, CREDIT_NOT_THERE_YET) || 
     str_equal(status, CREDIT_PENDING)       || 
     str_equal(status, CREDIT_CHARGED)       || 
     str_equal(status, NOT_THERE_YET))
     return I_NOT_THERE_YET;
  else if(str_equal(status, PENDING))
    return I_PENDING;
  else if(str_equal(status, NIL) || str_equal(status, LOCKED))
    return I_CLEARED;
  else
    return NO_INDEX;
}
