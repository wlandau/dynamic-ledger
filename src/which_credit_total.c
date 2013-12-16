/***
 *** @file which_credit_total.c
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

index_t which_credit_total(char *status){
  if(status == NULL)
    return NO_INDEX;

  if(str_equal(status, CREDIT_NOT_THERE_YET))
     return I_NOT_THERE_YET;
  else if(str_equal(status, CREDIT_PENDING))
    return I_PENDING;
  else if(str_equal(status, CREDIT_CHARGED))
    return I_CLEARED;
  else
    return NO_INDEX;
}
