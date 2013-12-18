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
  err_t ret;
  Ledger *ledger = NULL;
  
  get_ledger(&ledger, L2, NULL, NULL);
  ret = print_ledger_to_filename(ledger, "../parse_char/");
  free_ledger(&ledger);
  printf("\nRET = %d\n", ret);
  printf("\n----\n");

  get_ledger(&ledger, L2, NULL, NULL);
  ret = print_ledger_to_filename(ledger, "out1.txt");
  printf("nrows = %d\n", ledger->nrows);
  free_ledger(&ledger);
  printf("\nRET = %d\n", ret);
  printf("\n----\n");
  
  get_ledger(&ledger, L2, NULL, NULL);
  ret = print_ledger_to_filename(ledger, "out2.txt");
    printf("nrows = %d\n", ledger->nrows);
  free_ledger(&ledger);
  printf("\nRET = %d\n", ret);
  printf("\n----\n");
  
  get_ledger(&ledger, L3, NULL, NULL);
  ret = print_ledger_to_filename(ledger, "out3.txt");
    printf("nrows = %d\n", ledger->nrows);
  free_ledger(&ledger);
  printf("\nRET = %d\n", ret);
  
  return 0;
}
