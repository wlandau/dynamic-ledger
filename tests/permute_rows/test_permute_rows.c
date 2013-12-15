#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/basic.txt"

int main(){
  int *order, i;

  Ledger *ledger = NULL;
  printf("1 RET = %d\n", permute_rows(ledger, NULL));
  
  get_ledger(&ledger, F, NULL, NULL);
  
  order = malloc(ledger->nrows * sizeof(int));
  
  for(i = 0; i < ledger->nrows; ++i)
    order[i] = i;
    
  order[5] = 6;
  order[6] = 7;  
  order[7] = 8;  
  order[8] = 5;  
  
  print_ledger_to_stream(ledger, stdout);
  printf("2 RET = %d\n", permute_rows(ledger, order));
  print_ledger_to_stream(ledger, stdout);
  
  free(order);
  free_ledger(&ledger); 
  
  return 0;
}
