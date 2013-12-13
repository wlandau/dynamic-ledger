/***
 *** @file bad_output_file.c
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

bool_t output_file(const char *filename){
  FILE *fp = fopen(filename, "w");
  if(fp == NULL){
    fprintf(stderr, 
            "Error: cannot create file, %s.\nCheck your permissions.\n", filename);
    return LNO;
  }
  fclose(fp);
  return LYES;
}
