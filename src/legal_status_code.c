/**
 * @file        legal_status_code.c
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
 * @details Checks if a character string is one of the legal
 *          status codes defined in the Status_Macros module.
 *          The empty string NIL is also acceptable.
 */ 
bool_t legal_status_code(char *s){
  int ret;

  ret = str_equal(CREDIT_NOT_THERE_YET, s) ||
        str_equal(CREDIT_PENDING      , s) ||  
        str_equal(CREDIT_CHARGED      , s) ||  
        str_equal(NOT_THERE_YET       , s) ||  
        str_equal(PENDING             , s) ||
        str_equal(LOCKED              , s) ||  
        str_equal(NIL                 , s);
    
  return ret ? LYES : LNO;
}
