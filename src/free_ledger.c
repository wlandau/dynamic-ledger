/**
 * @file        free_ledger.c
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
 * @details Frees a whole ledger object and sets the pointer to NULL.
 *          so that the program knows that it is freed.
 */
err_t free_ledger(Ledger **ledger){

  err_t ret = LSUCCESS;

  if(ledger == NULL)
    return LFAILURE;
    
  if(*ledger == NULL)
    return LFAILURE;

  if((*ledger)->filename != NULL){
    free((*ledger)->filename);
    (*ledger)->filename = NULL;
  }
  
  if(free_entries(*ledger) == LFAILURE)
    ret = LFAILURE; 

  free(*ledger);
  *ledger = NULL;
  
  return ret;
}
