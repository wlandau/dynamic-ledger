#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/simple.txt"

int main(){
  int rows[] = {0, 1};
  Ledger *ledger = NULL, *clipboard = NULL;
  
  printf("\nTEST 1: RET = %d\n", copy_rows(ledger, &clipboard, rows, 5));
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("\nTEST 2: RET = %d\n", copy_rows(ledger, &clipboard, rows, 2));
  printf("\nTEST 2: RET = %d\n", paste_rows(ledger, clipboard, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("\nTEST 3: RET = %d\n", copy_rows(ledger, &clipboard, rows, 2));
  printf("\nTEST 3: RET = %d\n", paste_rows(ledger, clipboard, ledger->nrows));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("\nTEST 4: RET = %d\n", copy_rows(ledger, &clipboard, rows, 2));
  printf("\nTEST 4: RET = %d\n", paste_rows(ledger, clipboard, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("\nTEST 5: RET = %d\n", copy_rows(ledger, &clipboard, rows, 0));
  printf("\nTEST 5: RET = %d\n", paste_rows(ledger, clipboard, ledger->nrows));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  free_ledger(&ledger);
  free_ledger(&clipboard);
  return 0;
}
