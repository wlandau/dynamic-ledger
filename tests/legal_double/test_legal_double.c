#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){

  char str[1000];
  
  strcpy(str, "  l  -14.2 ");
  printf("%s\t%d\n", str, legal_double(str));
  printf("%s\n", str);
  
  strcpy(str, "    -14.2 \t\t ");
  printf("%s\t%d\n", str, legal_double(str));
  printf("%s\n", str);
  
  return 0;
}
