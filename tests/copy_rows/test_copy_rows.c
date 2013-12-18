#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/basic.txt"

int main(){
  int rows[] = {2, 1, 2, 3, 6};
  Ledger *ledger = NULL, *clipboard = NULL;
  
  printf("\nTEST 1: RET = %d\n", copy_rows(ledger, &clipboard, rows, 5));
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("\nTEST 2: RET = %d\n", copy_rows(ledger, &clipboard, rows, 5));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("PRINTING CLIPBOARD\n");
  print_ledger_to_stream(clipboard, stdout);  
  
  free_ledger(&ledger);
  
  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  printf("\nTEST 3: RET = %d\n", copy_rows(ledger, &clipboard, rows, 5));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("PRINTING CLIPBOARD\n");
  print_ledger_to_stream(clipboard, stdout);  
  
  free_ledger(&clipboard);
    free_ledger(&ledger);
  return 0;
}
