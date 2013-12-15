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
 
  printf("TEST 1 RET = %d\n", modify_entry(ledger, 0, 0, "hi"));
  
  get_ledger(&ledger, F, NULL, NULL);
  
  print_ledger_verbose(ledger, stdout);
  printf("\nTEST 2 RET = %d\n", modify_entry(ledger, 0, 0, "hi"));
/*
  print_ledger_verbose(ledger, stdout);
  printf("\nTEST 3 RET = %d\n", modify_entry(ledger, 0, 3, "hi"));
  print_ledger_verbose(ledger, stdout);
  

  printf("\nTEST 4 RET = %d\n", modify_entry(ledger, -5, 3, "hi"));
  printf("\nTEST 5 RET = %d\n", modify_entry(ledger, 1000, 3, "hi"));
  printf("\nTEST 6 RET = %d\n", modify_entry(ledger, 0, -5, "hi"));
  printf("\nTEST 7 RET = %d\n", modify_entry(ledger, 1000, 1000, "hi"));


  printf("\nTEST 8 RET = %d\n", modify_entry(ledger, 0, 1, "hi"));
  print_ledger_verbose(ledger, stdout);

  printf("\nTEST 9 RET = %d\n", modify_entry(ledger, 0, 1, "c"));
  print_ledger_verbose(ledger, stdout);
  
  printf("\nTEST 10 RET = %d\n", modify_entry(ledger, 2, 0, "c"));
  print_ledger_verbose(ledger, stdout);

  printf("\nTEST 11 RET = %d\n", modify_entry(ledger, 2, 0, "0.5"));
  print_ledger_verbose(ledger, stdout);
*/
  free_ledger(&ledger);
  return 0;
}
