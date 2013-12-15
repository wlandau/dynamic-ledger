#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L2 "../data/ledgers/empty.txt"
#define L3 "../data/ledgers/basic.txt"

int main(){
  Ledger *ledger = NULL;
  printf("0 RET = %d\n", print_ledger_verbose(ledger, stdout));
  
  new_ledger(&ledger);
  printf("1 RET = %d\n", print_ledger_verbose(ledger, stdout));
  free_ledger(&ledger);
  
  get_ledger(&ledger, L2, NULL, NULL);
  printf("2 RET = %d\n", print_ledger_verbose(ledger, stdout));
  free_ledger(&ledger);
  
  printf("\n\n--------\n\n");

  get_ledger(&ledger, L3, NULL, NULL);
  printf("3 RET = %d\n", print_ledger_verbose(ledger, stdout));
  free_ledger(&ledger);
  

  return 0;
}
