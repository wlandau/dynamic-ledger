#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L3 "../data/ledgers/basic.txt"

int main(){
  Ledger *ledger = NULL;
  
  printf("1 RET = %d\n", free_ledger(NULL));
  printf("2 RET = %d\n", free_ledger(&ledger));
  printf("3 RET = %d\n", free_ledger(&ledger));
    
  new_ledger(&ledger);
  printf("4 RET = %d\n", free_ledger(&ledger));
  printf("5 RET = %d\n", free_ledger(&ledger));

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  printf("6 RET = %d\n", free_ledger(&ledger));

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  get_totals(ledger);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  printf("7 RET = %d\n", free_ledger(&ledger));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  printf("8 RET = %d\n", free_ledger(&ledger));

  return 0;
}
