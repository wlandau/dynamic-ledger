/**
 * @file        col_delim_str.c
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
 * @details Loops through the characters in the argument
 *          character string and returns the index of the 
 *          first character that is a column separator.
 *          if no column separator is found, the function
 *          returns no_index.
 */
index_t col_delim_str(char *s){
  int i, n;
  
  if(s == NULL)
    return NO_INDEX;
    
  n = strlen(s);  
  
  for(i = 0; i < n; ++i)
    if(col_delim_char(s[i]))
      return i;
  return NO_INDEX;
}
