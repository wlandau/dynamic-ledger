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
  printf("\n----\n1 RETURN VALUE = %d\n---\n", ret);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  new_ledger(&ledger);
  
  ret = alloc_totals(ledger);
  printf("\n----\n2 RETURN VALUE = %d\n---\n", ret);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  ledger->nrows = 0;

  ret = alloc_totals(ledger);
  printf("\n----\n3 RETURN VALUE = %d\n---\n", ret);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  ret = alloc_entries(ledger);

  ret = alloc_totals(ledger);
  printf("\n----\n3A RETURN VALUE = %d\n---\n", ret);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  ledger->nrows = 4;
  ret = alloc_totals(ledger);
  printf("\n----\n4 RETURN VALUE = %d\n---\n", ret);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  alloc_entries(ledger);
  ret = alloc_totals(ledger);
  printf("\n----\n5 RETURN VALUE = %d\n---\n", ret);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  get_names(ledger);
  ret = alloc_totals(ledger);
  printf("\n----\n6 RETURN VALUE = %d\n---\n", ret);  
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/basic.txt", NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  free_ledger(&ledger);

  return 0;
}
