#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char str[1000];

  printf("\"NULL\" ret = %d\n", col_delim_str(NULL));  

  strcpy(str, "	hi");
  printf("\"%s\" ret = %d\n", str, col_delim_str(str));
  
  strcpy(str, "goobah	klj");
  printf("\"%s\" ret = %d\n", str, col_delim_str(str));

  strcpy(str, "	doogdoogie");
  printf("\"%s\" ret = %d\n", str, col_delim_str(str));
  
  strcpy(str, "DERP!");
  printf("\"%s\" ret = %d\n", str, col_delim_str(str));
  
  strcpy(str, "DE	RP!");
  printf("\"%s\" ret = %d\n", str, col_delim_str(str));
  return 0;
}
