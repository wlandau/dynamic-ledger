/**
 * @file        row_delim_str.c
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
 * @details Loops through the characters in the argument
 *          character string and returns the index of the 
 *          first character that is a row separator.
 *          if no row separator is found, the function
 *          returns no_index.
 */
index_t row_delim_str(char *s){
  int i, n;
  
  if(s == NULL)
    return NO_INDEX;

  n = strlen(s);

  for(i = 0; i < n; ++i)
    if(row_delim_char(s[i]))
      return i;
  return NO_INDEX;
}
