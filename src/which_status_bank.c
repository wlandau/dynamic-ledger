/***
 *** @file alloc_text_content.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

index_t which_status_bank(char *status){
  if(status == NULL)
    return NO_INDEX;
    
  if(str_equal(status, CREDIT_NOT_THERE_YET) || 
     str_equal(status, CREDIT_PENDING)       || 
     str_equal(status, CREDIT_CHARGED)       || 
     str_equal(status, NOT_THERE_YET))
     return I_NOT_THERE_YET;
  else if(str_equal(status, PENDING))
    return I_PENDING;
  else if(str_equal(status, NIL) || str_equal(status, LOCKED))
    return I_CLEARED;
  else
    return NO_INDEX;
}
