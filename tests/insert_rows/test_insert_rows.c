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
  
  printf("RET = %d\n", insert_rows(ledger, 3, 3));
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);

  printf("RET = %d\n", insert_rows(ledger, -1, 3));
  printf("RET = %d\n", insert_rows(ledger, 1000, 3));

  printf("RET = %d\n", insert_rows(ledger, 3, 3));
  print_ledger_to_stream(ledger, stdout); 
   
  printf("RET = %d\n", insert_rows(ledger, 8, 5));  
  print_ledger_to_stream(ledger, stdout); 
  
  free_ledger(&ledger);
  return 0;
}
