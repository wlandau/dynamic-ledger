#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  printf("%s %d\n", NULL, which_bank_total(NULL));
  printf("%s %d\n", NIL, which_bank_total(NIL));
  printf("%s %d\n", "\0" ,which_bank_total("\0"));
  printf("%s %d\n\n", "", which_bank_total(""));
  printf("%s %d\n", "cn", which_bank_total("cn"));  
  printf("%s %d\n", "cp", which_bank_total("cp"));
  printf("%s %d\n", "c", which_bank_total("c"));
  printf("%s %d\n", "n", which_bank_total("n"));
  printf("%s %d\n", "p", which_bank_total("p"));
  printf("%s %d\n", "l", which_bank_total("l"));
  printf("%s %d\n", "alskfdj", which_bank_total("alskfdj"));
  return 0;
}
