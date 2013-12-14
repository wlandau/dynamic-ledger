#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  
  printf("%shigh\n", color(9, 1));
  printf("%szero\n", color(0.001, 1));
  printf("%slow\n", color(-9, 1));
  printf("%sback to normal.\n", NORMAL_COLOR);
  
  
  printf("%shigh\n", color(9, 0));
  printf("%szero\n", color(0.001, 0));
  printf("%slow\n", color(-9, 0));
  printf("%sback to normal.\n", NORMAL_COLOR);
  
  return 0;
}
