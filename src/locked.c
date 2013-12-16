/***
 *** @file locked.c
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

bool_t locked(char *status){
  if(status == NULL)
    return LNO;

  bool_t ret = str_equal(status, CREDIT_NOT_THERE_YET) ||
               str_equal(status, CREDIT_PENDING)       ||
               str_equal(status, CREDIT_CHARGED)       ||
               str_equal(status, NOT_THERE_YET)        ||
               str_equal(status, PENDING)              ||
               str_equal(status, LOCKED);
  return ret ? LYES : LNO;
}
