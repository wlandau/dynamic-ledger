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
  int rows[] = {-1, 0, 2, 10};
  char entrynumber[] = "9";
  char entrystr[] = "  sacrebleu!";
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("1 RET = %d\n", map_to_column(ledger, entrynumber, rows, 4, 0, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("2 RET = %d\n", map_to_column(ledger, entrynumber, NULL, 4, 0, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
 
  printf("3 RET = %d\n", map_to_column(ledger, entrynumber, rows, 4, 0, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("4 RET = %d\n", map_to_column(ledger, entrynumber, rows, 4, 0, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  
  printf("4 RET = %d\n", map_to_column(ledger, entrystr, rows, 4, 5, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("5 RET = %d\n", map_to_column(ledger, entrystr, rows, 4, 5, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  
  printf("6 RET = %d\n", map_to_column(ledger, entrystr, rows, 4, 1, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("7 RET = %d\n", map_to_column(ledger, entrystr, rows, 4, 2, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  free_ledger(&ledger);

  return 0;
}
