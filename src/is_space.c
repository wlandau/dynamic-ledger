/***
 *** @file is_space.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_space(char c){
  return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == 'v');
}
