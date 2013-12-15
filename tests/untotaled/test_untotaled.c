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
  
  printf("RET = %d\n", untotaled(ledger));
  new_ledger(&ledger);
  printf("RET = %d\n", untotaled(ledger));
  free_ledger(&ledger);
  get_ledger(&ledger, F, NULL, NULL);
  printf("RET = %d\n", untotaled(ledger));

  free_ledger(&ledger);
  

  return 0;
}
