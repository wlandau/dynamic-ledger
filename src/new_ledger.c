/**
 * @file        new_ledger.c
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
 * @details Creates a new Ledger object. Pointers are initialized
 *          to NULL so that the program knows that they do not point
 *          to any meaningful memory. ledger should point to NULL
 *          if it is empty.
 */
err_t new_ledger(Ledger **ledger){
  free_ledger(ledger);

  *ledger = calloc(1, sizeof(Ledger));
  
  if(*ledger == NULL){
    fprintf(stderr, "Error: calloc failed.\n");
    return LFAILURE;
  }
  
  (*ledger)->nbanks = 0;
  (*ledger)->ncredits = 0;
  (*ledger)->nrows = 0;
  (*ledger)->banks = NULL;
  (*ledger)->bank_totals = NULL;
  (*ledger)->credits = NULL;
  (*ledger)->credit_totals = NULL;
  (*ledger)->entries= NULL;
  (*ledger)->filename = NULL;
  (*ledger)->npartitions = NULL;
  (*ledger)->partitions = NULL;
  (*ledger)->partition_totals = NULL;
  
  return LSUCCESS; 
}

