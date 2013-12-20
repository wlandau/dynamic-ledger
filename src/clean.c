/**
 * @file clean.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details  Cleans a ledger object. Specifically, calls condense 
 *           and sort_by_status.
 */
err_t clean(Ledger *ledger, int sort_locked){
  
  if(condense(ledger) == LFAILURE)
    return LFAILURE;

  if(sort_by_status(ledger, sort_locked) == LFAILURE)
    return LFAILURE;
 
  return LSUCCESS;
}
