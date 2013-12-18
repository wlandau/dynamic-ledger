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
  
  printf("1 RET = %d\n", insert_rows(ledger, 3, 3));
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("2 RET = %d\n", insert_rows(ledger, -1, 3));
  printf("3 RET = %d\n", insert_rows(ledger, 1000, 3));

  printf("4 RET = %d\n", insert_rows(ledger, 3, 3));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
   
  printf("5 RET = %d\n", insert_rows(ledger, 8, 5));  
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);


  printf("6 RET = %d\n", insert_rows(ledger, ledger->nrows, 4)); 
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("7 RET = %d\n", insert_rows(ledger, 0, 4)); 
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("8 RET = %d\n", insert_rows(ledger, 90898, 0)); 
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
    
  free_ledger(&ledger);
  
  printf("empty ledgers...\n");
  new_ledger(&ledger);

  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("9 RET = %d\n", insert_rows(ledger, 0, 5));  
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  get_names(ledger);
  get_totals(ledger);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  edit_entry(ledger, "1", 0, AMOUNT);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  free_ledger(&ledger);
  return 0;
}
