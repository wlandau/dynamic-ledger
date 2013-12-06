/***
 *** @file bad_output_file.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bad_output_file(const char *filename){
  FILE *fp = fopen(filename, "w");
  if(fp == NULL){
    fprintf(stderr, 
            "Error: cannot create file, %s.\nCheck your permissions.\n", filename);
    return 1;
  }
  fclose(fp);
  return 0;
}
