/***
 *** @file bad_input_file.c
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

bool_t input_file(const char *filename){
  FILE *fp = fopen(filename, "r");
  if(fp == NULL){
    fprintf(stderr, "Error: cannot open file, %s.\nFile may not exist.\n", filename);
    return LNO;
  }
  fclose(fp);
  return LYES;
}
