/**
 * @file        legal_status_codes.c
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
 * @details Checks if all the character strings in the
 *          STATUS column of the ledger are legal
 *          status codes as defined in the Status_Macros module.
 *          Specifically, it loops through ledger->entries[STATUS]
 *          and calls legal_status_code on every entry.
 *          The empty string, NIL, is also legal.
 */ 
bool_t legal_status_codes(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return LNO;

  for(i = 0; i < ledger->nrows; ++i)
    if(legal_status_code(ledger->entries[STATUS][i]) == LNO){
      fprintf(stderr, "Error: illegal transaction status code \"%s\" at line %d\n",
              ledger->entries[STATUS][i], i + 1);
      return LNO;
    }
    
  return LYES;
}
