/***
 *** @file legal_double.c
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

bool_t legal_double(char *s){
  int e = 0;
  char *testbufref, testbuf[ENTRYSIZE];
  
  str_strip(s);
  strcpy(testbuf, s);
  testbufref = testbuf;

  errno = 0;
  strtod(testbuf, &testbufref); 
  e = errno;

  if((e || testbuf == testbufref || *testbufref != 0) && strlen(testbuf))
    return LNO;   

  return LYES;
}
