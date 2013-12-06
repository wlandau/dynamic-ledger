/***
 *** @file str_equal.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int str_equal(const char *s1, const char *s2){
  return !strcmp(s1, s2) && (strlen(s1) == strlen(s2));
}
