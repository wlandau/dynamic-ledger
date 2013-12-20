#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  Ledger *ledger = NULL;
  int ret = new_ledger(&ledger);
  free_ledger(&ledger);
  printf("stat = %d\n", ret);
  return 0;
}
