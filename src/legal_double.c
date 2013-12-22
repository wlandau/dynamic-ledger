/**
 * @file        legal_double.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Checks if a character string can be converted into
 *          a meaningful floating point number. Uses errno.h
 *          to do so.
 */
bool_t legal_double(char *s){
  int e = 0;
  char *testbufref, testbuf[ENTRYSIZE];
  
  if(strlen(s) >= ENTRYSIZE)
    return LNO;
  
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
