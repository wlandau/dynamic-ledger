#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char good[400], bad[400];
  strcpy(good, "../../ledgers/ledgers/basic.txt");
  printf("\nError status = %d for file, %s\n", bad_input_file(good), good);

  strcpy(bad, "DERP");
  printf("\nError status = %d for file, %s\n", bad_input_file(bad), bad);

  return 0;
}
