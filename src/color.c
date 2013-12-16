/***
 *** @file color.c
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

color_t color(double d, int usecolor){ 
  if(!usecolor)
    return "";
  
  if(d > EPS)
    return POSITIVE_COLOR;
  else if(d < -EPS)
    return NEGATIVE_COLOR;
  else 
    return ZERO_COLOR;
}
