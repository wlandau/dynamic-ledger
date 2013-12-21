/**
 * @file        which.c
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
 * @details Finds an occurrence of the character string, "find",
 *          in the array of character strings, "s", using binary
 *          search. The index returned need not be the index of 
 *          the first occurrence. Returns NO_INDEX if "find"
 *          is not an element of s.
 */ 
index_t which(char **s, char *find, int n){
  int low = 0, high = n - 1, mid, c;
  
  if(s == NULL || find == NULL || n < 1)
    return NO_INDEX;
    
  while(abs(high - low) > 1){
    mid = (high + low)/2;
    c = strcmp(s[mid], find);
    if(c > 0)
      high = mid;
    else if(c < 0)
      low = mid;
    else
      low = high = mid;
  }  
 
  if(!strcmp(s[low], find))
    return low;
  else if(!strcmp(s[high], find))
    return high;
  else
    return NO_INDEX;
}
