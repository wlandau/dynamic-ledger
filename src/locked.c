/**
 * @file        locked.c
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
 * @details  Checks if a status code "locks" a transaction.
 *           Any transaction with a legal status code not equal to
 *           NIL or REMOVE is "locked": that is, it will be ignored 
 *           by the trim_ledger, condense, and clean functions.        
 */  
bool_t locked(char *status){
  bool_t ret;
  
  if(status == NULL)
    return LNO;

  ret = str_equal(status, CREDIT_NOT_THERE_YET) ||
        str_equal(status, CREDIT_PENDING)       ||
        str_equal(status, CREDIT_CHARGED)       ||
        str_equal(status, NOT_THERE_YET)        ||
        str_equal(status, PENDING)              ||
        str_equal(status, LOCKED);
  return ret ? LYES : LNO;
}
