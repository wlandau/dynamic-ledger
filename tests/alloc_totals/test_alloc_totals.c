#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  int ret;
  Ledger *ledger = NULL;
  
  ret = alloc_totals(ledger);
  printf("\n----\nRETURN VALUE = %d\n---\n", ret);

  new_ledger(&ledger);
  ret = alloc_totals(ledger);
  printf("\n----\nRETURN VALUE = %d\n---\n", ret);
  
  ledger->nrows = 4;
  ret = alloc_totals(ledger);
  printf("\n----\nRETURN VALUE = %d\n---\n", ret);
  
  alloc_entries(ledger);
  ret = alloc_totals(ledger);
  printf("\n----\nRETURN VALUE = %d\n---\n", ret);
  
  get_names(ledger);
  ret = alloc_totals(ledger);
  printf("\n----\nRETURN VALUE = %d\n---\n", ret);  
  
  free_ledger(&ledger);
  return 0;
}
