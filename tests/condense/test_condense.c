#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L0 "../data/ledgers/basic.txt"
#define L1 "../data/ledgers/example_ledger.txt"
#define L2 "../data/ledgers/empty.txt" 

int main(){
  int i, test, ntests = 3;
  Ledger *ledger = NULL;
  char **strs;

  strs = malloc(ntests * sizeof(char*));
  for(i = 0; i < ntests; ++i)
    strs[i] = calloc(2000, sizeof(char));

  strcpy(strs[0], L0);
  strcpy(strs[1], L1);
  strcpy(strs[2], L2);

  printf("\n--------\nTEST -2 | ret = %d\n", condense(ledger));

  new_ledger(&ledger);
  printf("\n--------\nTEST -1 | ret = %d\n", condense(ledger));
  free_ledger(&ledger);

 for(test = 0; test < 3; ++test){
    printf("\n--------\nTEST %d", test);
    get_ledger(&ledger, strs[test], NULL, NULL);
    print_ledger_verbose(ledger, stdout);
    printf("\nret = %d\n", condense(ledger));
    print_ledger_verbose(ledger, stdout);   
    free_ledger(&ledger);
    free(strs[test]);
  }  

  free(strs);
  return 0;
}
