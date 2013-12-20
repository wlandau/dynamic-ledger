/**
 * @file filled_partitions.c
 * @author Will Landau (http://www.will-landau.com/)
 * @details Loops through all the partitions of a given 
 *          bank account in a Ledger object. Returns LYES
 *          if any partition (including the unnamed partition)
 *          is found to have a nonzero amount. Returns LNO otherwise.
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

bool_t filled_partitions(Ledger *ledger, int bank){
  int i;
  bool_t ret = LNO;
 
  /* Checking for good input */
  
  if(ledger == NULL) 
    return LNO;
   
  if(ledger->nrows < 1 || bank < 0 || bank >= ledger->nbanks)
    return LNO;  
 
  if(untotaled(ledger) == LYES)
    return LNO;

  /* Find nonempty partitions */ 

  for(i = 0; i < ledger->npartitions[bank]; ++i)
    if(small_norm(ledger->partition_totals[bank][i]) == LNO){
      ret = LYES;
      break;
    }

  return ret;
}
