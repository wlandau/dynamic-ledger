#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  
  printf("%sset background\n", BACKGROUND_COLOR);
  printf("%shigh\n", get_color(9));
  printf("%szero\n", get_color(0.001));
  printf("%slow\n", get_color(-9));
  printf("%sback to normal.\n", NORMAL_COLOR);
  
  return 0;
}
