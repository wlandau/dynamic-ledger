#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>


#define F "../data/ledgers/example_ledger2.txt"

int main(){
  int i;
  Ledger *ledger = NULL;

  printf("\n--------\nTEST 1 | ret = %d\n",  remove_rows(ledger));

  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_verbose(ledger, stdout);
  printf("\n--------\nTEST 2 | ret = %d\n",  remove_rows(ledger));
  print_ledger_verbose(ledger, stdout);
  
  for(i = 0; i < ledger->nrows; ++i)
    if(i == 2 || i == 6 || i == 7 || i == 8)
      strcpy(ledger->entries[STATUS][i], REMOVE);
   
  printf("\n--------\nTEST 3 | ret = %d\n",  remove_rows(ledger));
  print_ledger_verbose(ledger, stdout);
  free_ledger(&ledger);
  
  
  get_ledger(&ledger, F, NULL, NULL);
  for(i = 0; i < ledger->nrows; ++i)
    strcpy(ledger->entries[STATUS][i], REMOVE);
  printf("\n--------\nTEST 3 | ret = %d\n",  remove_rows(ledger));
  print_ledger_verbose(ledger, stdout);
  
  free_ledger(&ledger);  
  return 0;
}
