#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/basic.txt"

int main(){
  int *rows;

  Ledger *ledger = NULL;
  printf("0 RET = %d\n", move_rows(ledger, NULL, 0, 0));
  
  get_ledger(&ledger, F, NULL, NULL);
  
  rows = malloc(3 * sizeof(int));
    
  rows[0] = 3; 
  rows[1] = 8;  
  rows[2] = 9;  
  
  print_ledger_to_stream(ledger, stdout);
  printf("1 RET = %d\n", move_rows(ledger, rows, 3, 0));
  print_ledger_to_stream(ledger, stdout);
 
  rows[0] = 0; 
  rows[1] = 2;  
  rows[2] = 1;  
  printf("2 RET = %d\n", move_rows(ledger, rows, 3, ledger->nrows));
    print_ledger_to_stream(ledger, stdout);
  
  rows[0] = 4; 
  rows[1] = 6;  
  rows[2] = 3;  
  
  printf("3 RET = %d\n", move_rows(ledger, rows, 3, 0));
    print_ledger_to_stream(ledger, stdout);
  
  free(rows);
  free_ledger(&ledger); 
  
  return 0;
}
