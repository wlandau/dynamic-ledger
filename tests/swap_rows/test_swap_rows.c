#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/basic.txt"

int main(){

  Ledger *ledger = NULL;
  
  printf("1 RET = %d\n", swap_rows(ledger, 0, 0));
  
  new_ledger(&ledger);
  print_ledger_to_stream(ledger, stdout);
  printf("2 RET = %d\n", swap_rows(ledger, 0, 0));
    print_ledger_to_stream(ledger, stdout);
  printf("3 RET = %d\n", swap_rows(ledger, 0, 1));
    print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger);
  
  get_ledger(&ledger, F, NULL, NULL);
    print_ledger_to_stream(ledger, stdout);
          printf("4A RET = %d\n", swap_rows(ledger, -5, 6));
      printf("4B RET = %d\n", swap_rows(ledger, 500, 6));
          printf("4C RET = %d\n", swap_rows(ledger, 3, -5));
      printf("4D RET = %d\n", swap_rows(ledger, 3, 500));
      printf("4 RET = %d\n", swap_rows(ledger, 3, 6));
    print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
    print_ledger_to_stream(ledger, stdout);
  printf("EMPTY RET = %d\n", swap_rows(ledger, 0, 0));  
    print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger); 
  
  return 0;
}
