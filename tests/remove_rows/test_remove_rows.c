#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>


#define F "../data/ledgers/example_ledger2.txt"

int main(){
  int i, *remove;
  Ledger *ledger = NULL;

  printf("\n--------\nTEST -2 | ret = %d\n",  remove_rows(ledger, 0));

  get_ledger(&ledger, F, NULL, NULL);
  printf("\n--------\nTEST -1 | ret = %d\n",  remove_rows(ledger, NULL));

  remove = calloc(ledger->nrows, sizeof(int));  
  for(i = 0; i < ledger->nrows; ++i)
    if(i == 2 || i == 6 || i == 7 || i == 8)
      remove[i] = 1;

  print_ledger_verbose(ledger, stdout);
  printf("\n--------\nTEST -1 | ret = %d\n",  remove_rows(ledger, remove));
  print_ledger_verbose(ledger, stdout);

  free(remove);
  return 0;
}
