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
 
  printf("TEST 1 RET = %d\n", rename_partition(ledger, "hi", "ho", "hum"));
  
  get_ledger(&ledger, F, NULL, NULL);
  
  print_ledger_verbose(ledger, stdout);
  printf("\nTEST 2 RET = %d\n", rename_partition(ledger, "hi", "ho", "hum"));

  print_ledger_verbose(ledger, stdout);
  printf("\nTEST 3 RET = %d\n", rename_partition(ledger, "cp", "a", "humbug"));
  print_ledger_verbose(ledger, stdout);

  free_ledger(&ledger);
  return 0;
}
