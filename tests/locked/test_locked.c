#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  printf("%s %d\n", NULL, locked(NULL));
  printf("%s %d\n", NIL, locked(NIL));
  printf("%s %d\n", "\0" ,locked("\0"));
  printf("%s %d\n\n", "", locked(""));
  printf("%s %d\n", "cn", locked("cn"));  
  printf("%s %d\n", "cp", locked("cp"));
  printf("%s %d\n", "c", locked("c"));
  printf("%s %d\n", "n", locked("n"));
  printf("%s %d\n", "p", locked("p"));
  printf("%s %d\n", "l", locked("l"));
  printf("%s %d\n", "alskfdj", locked("alskfdj"));
  return 0;
}
