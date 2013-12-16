/***
 *** @file legal_status_code.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

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
