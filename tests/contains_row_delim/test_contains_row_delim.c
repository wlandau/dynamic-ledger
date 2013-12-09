#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char str[1000];

  strcpy(str, "	hi\n");
  printf("\"%s\" ret = %d\n", str, contains_row_delim(str));
  
  strcpy(str, "	goobah	");
  printf("\"%s\" ret = %d\n", str, contains_row_delim(str));

  strcpy(str, "doo\rgie	");
  printf("\"%s\" ret = %d\n", str, contains_row_delim(str));
  
  strcpy(str, "DER\nP!");
  printf("\"%s\" ret = %d\n", str, contains_row_delim(str));
  
  strcpy(str, "DE	RP!");
  printf("\"%s\" ret = %d\n", str, contains_row_delim(str));
  return 0;
}
