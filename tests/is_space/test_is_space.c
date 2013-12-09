#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  
  printf("%d\n", is_space(' '));
  printf("%d\n", is_space('\f'));
  printf("%d\n", is_space('\n'));  
  printf("%d\n", is_space('\r')); 
  printf("%d\n", is_space('\t')); 
  printf("%d\n\n", is_space('\v'));  

  printf("%d\n", is_space('f'));
  printf("%d\n", is_space('n'));
  printf("%d\n", is_space('r'));  
  printf("%d\n", is_space('t')); 
  printf("%d\n", is_space('v'));  
  printf("%d\n", is_space('.'));
  printf("%d\n", is_space('s'));    
  
  return 0;
}
