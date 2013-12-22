#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/simple.txt"

int main(){
  Ledger *ledger = NULL;
  int field;
  char **entries = malloc(NFIELDS * sizeof(char*));
  for(field = 0; field < NFIELDS; ++field)
    entries[field] = calloc(ENTRYSIZE, sizeof(char));

  strcpy(entries[AMOUNT], "aloha");
  strcpy(entries[STATUS], "squiggles");
  strcpy(entries[BANK], "newbank\tnewbank  ");
  strcpy(entries[CREDIT], "mycredit");
  strcpy(entries[PARTITION], "mypartition");
  strcpy(entries[DESCRIPTION], "dunkyhory\tblah");

  printf("TEST 1 RET = %d\n", edit_row(ledger, entries, 1, 0));

  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 2 RET = %d\n", edit_row(ledger, NULL, 1,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 3 RET = %d\n", edit_row(ledger, entries, 1,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  strcpy(entries[AMOUNT], "2000000");

  printf("TEST 4 RET = %d\n", edit_row(ledger, entries, 1,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  strcpy(entries[STATUS], "cn");

  printf("TEST 5 RET = %d\n", edit_row(ledger, entries, 1,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 6 RET = %d\n", edit_row(ledger, entries, -5,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 7 RET = %d\n", edit_row(ledger, entries, 5000,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);
  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  printf("TEST 10 RET = %d\n", edit_row(ledger, entries, 0,0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);
  free_ledger(&ledger);

  for(field = 0; field < NFIELDS; ++field)
    free(entries[field]);
  free(entries);

  return 0;
}
