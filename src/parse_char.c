/**
 * @file parse_char.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
  * @details Parse a character while reading a ledger from a file. 
  *          Non-separators will be read into the "entries" member 
  *          array of the Ledger object: specifically, 
  *          a non-separator character c will be concatenated 
  *          to the tail of ledger->entries[*field][*row] (i.e., we set 
  *          ledger->entries[*field][*row][char_index] = c). 
  *          If c is a separating character like a row separator 
  *          or a column separator, then a new entry will be started: 
  *          that is, *row and *field will be changed and *char_index
  *          will be reset to 0.
  */

err_t parse_char(Ledger *ledger, char c, int *char_index, int *field, int *row){
  if(col_delim_char(c)){ /* Move to the next column and start another entry. */
    *char_index = 0;
    ++(*field); 
  } else if(row_delim_char(c)){ /* Move to the next row and start another entry. */
    *char_index = 0;
    *field = 0;
    ++(*row); 
  } else if(*field < NFIELDS && *char_index < ENTRYSIZE - 1){ /* Add to the current entry. */
    ledger->entries[*field][*row][*char_index] = c;
    ++(*char_index); 
  } 
  
  return LSUCCESS;
}
