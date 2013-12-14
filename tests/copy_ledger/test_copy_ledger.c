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

  Ledger *ledger = NULL, *out_ledger = NULL;
  
  printf("RET = %d\n", copy_ledger(&out_ledger, ledger));
  
  get_ledger(&ledger, L2, NULL, NULL);
  print_ledger_verbose(ledger, stdout);

  printf("\n\n---COPY:---\n\n");

  printf("RET = %d\n", copy_ledger(&out_ledger, ledger));
  print_ledger_verbose(out_ledger, stdout);
  free_ledger(&ledger);
  free_ledger(&out_ledger);
  
  printf("\n\n--------\n\n");
  
  
  printf("RET = %d\n", copy_ledger(&out_ledger, ledger));
  
  get_ledger(&ledger, L3, NULL, NULL);
  print_ledger_verbose(ledger, stdout);

  printf("\n\n---COPY:---\n\n");

  printf("RET = %d\n", copy_ledger(&out_ledger, ledger));
  print_ledger_verbose(out_ledger, stdout);
  free_ledger(&ledger);
  free_ledger(&out_ledger);
  

  return 0;
}
