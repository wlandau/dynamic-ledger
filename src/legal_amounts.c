/**
 * @file        legal_amounts.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Loops through all the entries in the AMOUNTS column
 *          of the given Ledger object and checks that all transaction
 *          amounts (stored as human-readable character strings)
 *          can be converted into meaningful floating point numbers.
 *          Specifically, it calls legal_double on every entry.
 *          The empty string is legal and taken to be 0.00.
 */
bool_t legal_amounts(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return LNO;

  for(i = 0; i < ledger->nrows; ++i)
    if(legal_double(ledger->entries[AMOUNT][i]) == LNO){
      fprintf(stderr, "Error: bad transaction amount \"%s\" at row %d.\n", 
              ledger->entries[AMOUNT][i], i + 1);
      fprintf(stderr, "Fix your ledger file.\n");
      return LNO;
    }

  return LYES;
}
