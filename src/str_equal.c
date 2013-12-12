/***
 *** @file str_equal.c
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
