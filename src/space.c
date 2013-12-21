/**
 * @file        space.c
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
 * @details Checks whether a character is a whitespace character,
 *          returns LYES if it is, and LNO otherwise.
 */
bool_t space(char c){
  if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
    return LYES;
  else
    return LNO;
}
