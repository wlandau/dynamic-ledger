/**
 * @file        swap_rows.c
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
 * @details Interchanges two rows of a Ledger object.
 *          Rows row1 and row2 of the "entries" member array 
 *          of the Ledger object are interchanged.
 */
err_t swap_rows(Ledger *ledger, int row1, int row2){
  int i;
  char tmp[ENTRYSIZE];
  
  /* Check for NULL input and bad row indices */
  
  if(ledger == NULL)
    return LFAILURE;
    
  if(ledger->nrows < 1 || ledger->entries == NULL)
    return LFAILURE;
    
  if(row1 < 0 || row1 >= ledger->nrows || row2 < 0 || row2 >= ledger->nrows){
    fprintf(stderr, "Error: illegal row index.\n");
    return LFAILURE;
  }
  
  /* Swap the rows */
  
  if(row1 == row2)
    return LSUCCESS;
    
  for(i = 0; i < NFIELDS; ++i){
    strcpy(tmp, ledger->entries[i][row1]);
    strcpy(ledger->entries[i][row1], ledger->entries[i][row2]);
    strcpy(ledger->entries[i][row2], tmp);  
  }
  
  return LSUCCESS;
}
