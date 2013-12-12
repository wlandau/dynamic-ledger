#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  Ledger *ledger = new_ledger();
  free_ledger(ledger);
  return 0;
}
