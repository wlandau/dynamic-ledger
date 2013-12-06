/***
 *** @file check_legal_double_modify.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_legal_double_modify(char *s){
  char *testbufref, testbuf[ENTRYSIZE];
  
  if(s == NULL)
    return 1;
  
  errno = 0;
  strcpy(testbuf, s);
    testbufref = testbuf;
    strtod(testbuf, &testbufref); 
    if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf)){
      fprintf(stderr, "Error: bad number.\n");
      return 1;   
    }
  return 0;
}
