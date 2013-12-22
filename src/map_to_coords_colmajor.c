/**
 * @file        map_to_coords_colmajor.c
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
 * @details Map a single character string to multiple entries 
 *          of a Ledger object. Specifically, ledger->entries[coords[0][i]][rows[1][i]] 
 *          is replaced with "entry", for i from 0 to length(coords) - 1. Set "append"
 *          to 0 to overwrite each entry, 1 to append to the head of each entry,
 *          and 2 to append to the tail of each entry. 
 */

err_t map_to_coords_colmajor(Ledger *ledger, char *entry, int **coords, 
                    int howmany, int append){
  int i;
  
  if(coords == NULL)
    return LFAILURE;

  if(coords[0] == NULL || coords[1] == NULL)
    return LFAILURE;
  
  for(i = 0; i < howmany; ++i)
    if(edit_entry_noretotal(ledger, entry, coords[0][i], coords[1][i], append) == LFAILURE) 
      continue;
      
  if(retotal(ledger) == LFAILURE)
    return LFAILURE; 
      
  return LSUCCESS;
}
