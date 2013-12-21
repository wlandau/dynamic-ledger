/**
 * @file        str_equal.c
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
 * @details  Checks whether two strings are equal.
 *           It uses strcmp for nonnull strings, but unlike strcmp, 
 *           it is safe to use with null char pointers.
 */
bool_t str_equal(const char *s1, const char *s2){
  if(s1 == NULL && s2 != NULL)
    return LNO;
  else if(s1 != NULL && s2 == NULL)    
    return LNO;
  else if(s1 == NULL && s2 == NULL)
    return LYES;
  else if(strcmp(s1, s2))
    return LNO;
  else
    return LYES;
}
