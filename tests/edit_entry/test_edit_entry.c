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
 
  printf("TEST 1 RET = %d\n", edit_entry(ledger, "hi", 0, 0, 1));
  
  get_ledger(&ledger, F, NULL, NULL);
  
  print_ledger_verbose(ledger, stdout);
  printf("\nTEST 2 RET = %d\n", edit_entry(ledger, "hi", 0, 0, 1));
  printf("\nTEST 2A RET = %d\n", edit_entry(ledger, NULL, 0, 0, 1));


  print_ledger_verbose(ledger, stdout);
    printf("\nTEST 2B RET = %d\n", edit_entry(ledger, NULL, 5, 0, 0));
    print_ledger_verbose(ledger, stdout);
  printf("\nTEST 2C RET = %d\n", edit_entry(ledger, NULL, 0, 0,  1));
    print_ledger_verbose(ledger, stdout);  
  printf("\nTEST 3 RET = %d\n", edit_entry(ledger, "hi", 0, 3, 1));
  print_ledger_verbose(ledger, stdout);
  

  printf("\nTEST 4 RET = %d\n", edit_entry(ledger, "hi", -5, 3,  1));
  printf("\nTEST 5 RET = %d\n", edit_entry(ledger, "hi", 1000, 3, 1));
  printf("\nTEST 6 RET = %d\n", edit_entry(ledger, "hi", 0, -5, 1));
  printf("\nTEST 7 RET = %d\n", edit_entry(ledger, "hi", 1000, 1000,  1));


  printf("\nTEST 8 RET = %d\n", edit_entry(ledger, "hi", 1, 1, 1));
  print_ledger_verbose(ledger, stdout);

  printf("\nTEST 9 RET = %d\n", edit_entry(ledger, "c", 1, 1, 1));
  print_ledger_verbose(ledger, stdout);
  
  printf("\nTEST 10 RET = %d\n", edit_entry(ledger, "c", 2, 0, 1));
  print_ledger_verbose(ledger, stdout);

  printf("\nTEST 11 RET = %d\n", edit_entry(ledger, "0.5", 2, 0, 1));
  print_ledger_verbose(ledger, stdout);

  printf("\nTEST 12 RET = %d\n", edit_entry(ledger, "200000", 2, 0, 0));
  print_ledger_verbose(ledger, stdout);

  free_ledger(&ledger);
  return 0;
}
