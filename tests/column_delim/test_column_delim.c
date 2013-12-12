#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char str[1000];

  strcpy(str, "	hi");
  printf("\"%s\" ret = %d\n", str, column_delim(str));
  
  strcpy(str, "goobah	klj");
  printf("\"%s\" ret = %d\n", str, column_delim(str));

  strcpy(str, "	doogdoogie");
  printf("\"%s\" ret = %d\n", str, column_delim(str));
  
  strcpy(str, "DERP!");
  printf("\"%s\" ret = %d\n", str, column_delim(str));
  
  strcpy(str, "DE	RP!");
  printf("\"%s\" ret = %d\n", str, column_delim(str));
  return 0;
}
