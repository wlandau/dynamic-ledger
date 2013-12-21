#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L0 "../data/ledgers/needtotrim.txt"
#define L1 "../data/ledgers/basic.txt"
#define L2 "../data/ledgers/example_ledger.txt"
#define L3 "../data/ledgers/empty.txt"

int main(){
  int i, test, ntests = 4;
  Ledger *ledger = NULL;
  char **strs;

  strs = malloc(ntests * sizeof(char*));
  for(i = 0; i < ntests; ++i)
    strs[i] = calloc(2000, sizeof(char));

  strcpy(strs[0], L0);
  strcpy(strs[1], L1);
  strcpy(strs[2], L2);
  strcpy(strs[3], L3);

  printf("\n--------\nTEST -1 | ret = %d\n",  trim_ledger(ledger));

  for(test = 0; test < ntests; ++test){
    printf("\n--------\nTEST %d\n", test);
    get_ledger(&ledger, strs[test], NULL, NULL);
    if(ledger->entries == NULL)
    printf("NULL ENTRIES\n");
    printf("nrows = %d\n", ledger->nrows);
    print_ledger_to_stream(ledger, stdout);
    printf("\nret = %d\n", trim_ledger(ledger));
    printf("nrows = %d\n", ledger->nrows);
    print_ledger_to_stream(ledger, stdout); 
    free_ledger(&ledger);
    free(strs[test]);
  }  

  free(strs);
  return 0;
}
