/***
 *** @file is_space.c
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

int is_space(char c){
  return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == 'v');
}
