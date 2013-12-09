/***
 *** @file get_color.c
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

const char *get_color(double d){ 
  if(!USE_COLOR)
    return "";
  
  if(d > EPS)
    return POSITIVE_COLOR;
  else if(d < -EPS)
    return NEGATIVE_COLOR;
  else 
    return ZERO_COLOR;
}
