/***
 *** @file space.c
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

bool_t space(char c){
  if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v')
    return LYES;
  else
    return LNO;
}
