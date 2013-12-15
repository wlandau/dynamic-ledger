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
  
  printf("1 RET = %d\n", filled_partitions(ledger, 0));
  new_ledger(&ledger);
  printf("2 RET = %d\n", filled_partitions(ledger, 0));
  free_ledger(&ledger);
  get_ledger(&ledger, F, NULL, NULL);
  printf("3 RET = %d\n", filled_partitions(ledger, which(ledger->banks, "cp", ledger->nbanks)));
  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  printf("EMPTY RET = %d\n", filled_partitions(ledger, 0));  
  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/small.txt", NULL, NULL);
  printf("SMALL RET = %d\n", filled_partitions(ledger, 0));  
  free_ledger(&ledger);  
  
  get_ledger(&ledger, "../data/ledgers/small.txt", NULL, NULL);
  printf("SMALL2 RET = %d\n", filled_partitions(ledger, 0));  
  free_ledger(&ledger);  
  
  return 0;
}
