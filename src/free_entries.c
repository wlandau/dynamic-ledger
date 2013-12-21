/**
 * @file        free_entries.c
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
 * @details Frees the "entries" member of a Ledger object.
 *          "entries" stores the entries of the Ledger spreadsheet
 *          with rows representing transactions and columns
 *          representing features of the transactions.
 */
err_t free_entries(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return LFAILURE;

  if(ledger->entries != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(ledger->entries[i] != NULL){
        for(j = 0; j < ledger->nrows; ++j)
          if(ledger->entries[i][j] != NULL){
            free(ledger->entries[i][j]);
            ledger->entries[i][j] = NULL;
          }
        free(ledger->entries[i]);
        ledger->entries[i] = NULL;
      }
    }
    free(ledger->entries);
    ledger->entries = NULL;
  }
  
  ledger->nrows = 0;  
  
  if(free_for_retotal(ledger) == LFAILURE)
    return LFAILURE;
  
  return LSUCCESS;
}
