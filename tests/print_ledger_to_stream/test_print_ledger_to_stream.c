#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L1 "../data/ledgers/nonnull.txt"
#define L2 "../data/ledgers/empty.txt"
#define L3 "../data/ledgers/basic.txt"

int main(){
  Ledger *ledger = NULL;
  
  get_ledger(&ledger, L1, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger);
  
  get_ledger(&ledger, L2, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger);
  
  printf("\n----\n");
  
  get_ledger(&ledger, L3, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger);  
  
  return 0;
}
