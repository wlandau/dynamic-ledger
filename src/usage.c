/***
 *** @file usage.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t usage(){
  printf("\nUsage: to summarize the ledger,\n$ ./ledger [LEDGER_FILE]\n");
  printf("\nTo condense the ledger,\n$ ");
  printf("./ledger [INTPUT_LEDGER_FILE] [OUTTPUT_LEDGER_FILE]\n");
  printf("\nSee README.txt for details.\n");
  
  return LSUCCESS;
}
