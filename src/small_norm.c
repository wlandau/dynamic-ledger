/**
 * @file small.c
 * @author Will Landau (http://www.will-landau.com/)
 */
 
#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/** 
 * @details  Checks whether a floating point number rounds to 0.00.
 *           Specifically, it checks if the square of the argument
 *           is less than EPS, returns LYES if so, and LNO otherwise.
 */
bool_t small_norm(double d){
  if((d * d) < EPS)
    return LYES;
  else
    return LNO;
}
