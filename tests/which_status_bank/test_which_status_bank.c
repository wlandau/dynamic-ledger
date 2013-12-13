#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  printf("%s %d\n", NULL, which_status_bank(NULL));
  printf("%s %d\n", NIL, which_status_bank(NIL));
  printf("%s %d\n", "\0" ,which_status_bank("\0"));
  printf("%s %d\n\n", "", which_status_bank(""));
  printf("%s %d\n", "cn", which_status_bank("cn"));  
  printf("%s %d\n", "cp", which_status_bank("cp"));
  printf("%s %d\n", "c", which_status_bank("c"));
  printf("%s %d\n", "n", which_status_bank("n"));
  printf("%s %d\n", "p", which_status_bank("p"));
  printf("%s %d\n", "alskfdj", which_status_bank("alskfdj"));
  return 0;
}
