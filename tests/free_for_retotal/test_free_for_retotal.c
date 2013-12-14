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
  
  printf("RET = %d\n", free_for_retotal(ledger));
  
  new_ledger(&ledger);
  printf("RET = %d\n", free_for_retotal(ledger));

  get_entries_from_filename(ledger, L3); 
  printf("RET = %d\n", free_for_retotal(ledger));
  
  get_names(ledger);
  printf("RET = %d\n", free_for_retotal(ledger));

  get_names(ledger);
  get_totals(ledger);

  printf("RET = %d\n", free_for_retotal(ledger));
  printf("RET = %d\n", free_for_retotal(ledger)); 
  free_ledger(&ledger);

  return 0;
}
