/**
 * @file        edit_entry.c
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
 * @details Overwrite an entry of a Ledger object with a new entry. 
 *          Specifically, ledger->entries[field][row] is replaced with 
 *          "entry", and the other data in the Ledger object is 
 *          updated with calls to get_names and get_totals. The append
 *          option works as in edit_entry_noretotal
 */

err_t edit_entry(Ledger *ledger, char *entry, int row, int field, int append){

  if(edit_entry_noretotal(ledger, entry, row, field, append) == LFAILURE)
    return LFAILURE;
        
  if(retotal(ledger) == LFAILURE)
    return LFAILURE; 
      
  return LSUCCESS;
}
