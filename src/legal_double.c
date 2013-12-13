/***
 *** @file check_legal_double.c
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

bool_t legal_double(char *s, int row){
  char *testbufref, testbuf[ENTRYSIZE];
  
  errno = 0;
  str_strip(s);
  strcpy(testbuf, s);
  testbufref = testbuf;
  strtod(testbuf, &testbufref); 

  if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf)){
    fprintf(stderr, "Error: bad number \"%s\" at row %d column 2.\n", 
            s, row + 1);
    fprintf(stderr, "Fix your ledger file.\n");
    return LNO;   
  }

  return LYES;
}
