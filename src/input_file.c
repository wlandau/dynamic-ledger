/***
 *** @file input_file.c
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

bool_t input_file(char *filename){
  FILE *fp;

  if(filename == NULL){
    fprintf(stderr, "Error: filename is null.\n");
    return LNO;
  }

  fp = fopen(filename, "r");
  if(fp == NULL){
    fprintf(stderr, "Error: cannot open file, %s.\nFile may not exist.\n", filename);
    return LNO;
  }
  fclose(fp);
  return LYES;
}
