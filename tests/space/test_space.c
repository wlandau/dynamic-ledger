#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  
  printf("%d\n", space(' '));
  printf("%d\n", space('\f'));
  printf("%d\n", space('\n'));  
  printf("%d\n", space('\r')); 
  printf("%d\n", space('\t')); 
  printf("%d\n\n", space('\v'));  

  printf("%d\n", space('f'));
  printf("%d\n", space('n'));
  printf("%d\n", space('r'));  
  printf("%d\n", space('t')); 
  printf("%d\n", space('v'));  
  printf("%d\n", space('.'));
  printf("%d\n", space('s'));    
  
  return 0;
}
