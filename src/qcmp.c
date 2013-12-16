/***
 *** @file qcmp.c
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

int qcmp(const void *a, const void *b){ 
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib); 
} 
