#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/example_ledger.txt"

int main(){

  Ledger *ledger = NULL;
  printf("0 RET = %d\n", sort_by_status(ledger, 0));
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  printf("1 RET = %d\n", sort_by_status(ledger, 1));
  print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger); 

  printf("\n\nTEST 2\n\n");
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  printf("2 RET = %d\n", sort_by_status(ledger, 0));
  print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger); 


  printf("\n\nTEST 3\n\n");
  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  printf("3 RET = %d\n", sort_by_status(ledger, 0));
  print_ledger_to_stream(ledger, stdout);
  free_ledger(&ledger); 
  
  return 0;
}
