#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L0 "../data/ledgers/basic.txt"
#define L1 "../data/ledgers/example_ledger.txt"
#define L2 "../data/ledgers/empty.txt" 

int main(){
  printf("%d\t%0.2f\n", small_norm(5.0), 5.0);
  printf("%d\t%0.2f\n", small_norm(.01), .01);
  printf("%d\t%0.2f\n", small_norm(.0051), .0051);  
  printf("%d\t%0.2f\n", small_norm(.0050), .0050); 
  printf("%d\t%0.2f\n", small_norm(.00499), .00499);  
  printf("%d\t%0.2f\n", small_norm(.0049), .0049);  
  printf("%d\t%0.2f\n", small_norm(-.0049), -.0049); 
  printf("%d\t%0.2f\n", small_norm(-.00499), -.00499); 
  printf("%d\t%0.2f\n", small_norm(-.0050), -.0050); 
  printf("%d\t%0.2f\n", small_norm(-.0051), -.0051);
  printf("%d\t%0.2f\n", small_norm(-.01), -.01);
  printf("%d\t%0.2f\n", small_norm(-5.0), -5.0);
  return 0;
}
