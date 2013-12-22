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
 
  printf("TEST 1 RET = %d\n", edit_entry(ledger, "hi", 1, 2, 0));
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 2 RET = %d\n", edit_entry(ledger, "hi", 1, 0, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 3 RET = %d\n", edit_entry(ledger, "0.5", 1, 0, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("TEST 3A RET = %d\n", edit_entry(ledger, "0.5", 1, 3, 1));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("TEST 3B RET = %d\n", edit_entry(ledger, "0.5", 2, 4, 2));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("TEST 3C RET = %d\n", edit_entry(ledger, "0.5", 1, 3, -1));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 4 RET = %d\n", edit_entry(ledger, "hi", 1, 1, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 5 RET = %d\n", edit_entry(ledger, "hi\thi", 1, 2, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 6 RET = %d\n", edit_entry(ledger, "hi\thi", -1, 2, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 7 RET = %d\n", edit_entry(ledger, "hi\thi", 1, -2, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 8 RET = %d\n", edit_entry(ledger, "hi\thi", 1000, 2, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  printf("TEST 9 RET = %d\n", edit_entry(ledger, "hi\thi", 1, 2000, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);
  free_ledger(&ledger);
  
  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  printf("TEST 10 RET = %d\n", edit_entry(ledger, "1000", 0, 0, 0));
  print_ledger_to_stream(ledger, stdout);  
  print_summary_to_stream(ledger, stdout, 1);

  free_ledger(&ledger);
  return 0;
}
