/***
 *** @file legal_double.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

bool_t legal_double(char *s){
  char *testbufref, testbuf[ENTRYSIZE];
  
  errno = 0;
  str_strip(s);
  strcpy(testbuf, s);
  testbufref = testbuf;
  strtod(testbuf, &testbufref); 

  if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf))
    return LNO;   

  return LYES;
}
