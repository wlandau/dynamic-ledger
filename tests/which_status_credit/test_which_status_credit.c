#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  printf("%s %d\n", NULL, which_status_credit(NULL));
  printf("%s %d\n", NIL, which_status_credit(NIL));
  printf("%s %d\n", "\0" ,which_status_credit("\0"));
  printf("%s %d\n\n", "", which_status_credit(""));
  printf("%s %d\n", "cn", which_status_credit("cn"));  
  printf("%s %d\n", "cp", which_status_credit("cp"));
  printf("%s %d\n", "c", which_status_credit("c"));
  printf("%s %d\n", "n", which_status_credit("n"));
  printf("%s %d\n", "p", which_status_credit("p"));
  printf("%s %d\n", "l", which_status_credit("l"));
  printf("%s %d\n", "alskfdj", which_status_credit("alskfdj"));
  return 0;
}
