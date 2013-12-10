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

int str_equal(const char *s1, const char *s2){
  return !strcmp(s1, s2);
}
