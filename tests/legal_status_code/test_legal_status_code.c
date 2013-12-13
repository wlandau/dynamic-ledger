#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  printf("%d\t%s\n", legal_status_code("cn"), "cn");
  printf("%d\t%s\n", legal_status_code("cp"), "cp");  
  printf("%d\t%s\n", legal_status_code("c"), "c");
  printf("%d\t%s\n", legal_status_code("n"), "n");
  printf("%d\t%s\n", legal_status_code("p"), "p");
  printf("%d\t%s\n", legal_status_code(""), "");
  printf("%d\t%s\n", legal_status_code("\0"), "\0");
  printf("%d\t%s\n", legal_status_code("-"), "-");   
  printf("%d\t%s\n", legal_status_code("cps"), "cps");        
  printf("%d\t%s\n", legal_status_code("goof"), "goof");        
}
