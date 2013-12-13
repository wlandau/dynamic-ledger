#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char good[400], bad[400];
  strcpy(good, "../data/ledgers/basic.txt");
  printf("\n\nError status = %d for file, %s\n\n", input_file(good), good);

  strcpy(bad, "DERP");
  printf("\n\nError status = %d for file, %s\n\n", input_file(bad), bad);

  return 0;
}
