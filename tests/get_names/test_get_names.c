#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L0 "../data/ledgers/bad.txt"
#define L1 "../data/ledgers/bad2.txt"
#define L2 "../data/ledgers/bad3.txt"
#define L3 "../data/ledgers/basic.txt"
#define L4 "../data/ledgers/condensed.txt"
#define L5 "../data/ledgers/empty.txt"
#define L6 "../data/ledgers/example_ledger.txt"
#define L7 "../data/ledgers/just_bank.txt"
#define L8 "../data/ledgers/justcredit.txt"
#define L9 "../data/ledgers/nonnull.txt"
#define L10 "../data/ledgers/small.txt"

int main(){
  int i, j, test, ntests = 11;
  Ledger *ledger = NULL;
  char **strs;

  strs = malloc(ntests * sizeof(char*));
  for(i = 0; i < ntests; ++i)
    strs[i] = calloc(2000, sizeof(char));

  strcpy(strs[0], L0);
  strcpy(strs[1], L1);
  strcpy(strs[2], L2);
  strcpy(strs[3], L3);
  strcpy(strs[4], L4);
  strcpy(strs[5], L5);
  strcpy(strs[6], L6);
  strcpy(strs[7], L7);
  strcpy(strs[8], L8);
  strcpy(strs[9], L9);
  strcpy(strs[10], L10);

  printf("\n--------\nTEST -1 | ret = %d\n",  get_entries_from_filename(ledger, NULL));

  for(test = 0; test < ntests; ++test){
    ledger = new_ledger();

    printf("\n--------\nTEST %d", test);
    printf("\nret = %d\n", get_entries_from_filename(ledger, strs[test]));
    
    printf("\nENTRIES %d\n\n", test); 
 
    for(j = 0; j < ledger->nrows; ++j){   
      for(i = 0; i < NFIELDS - 1; ++i)
        printf("%s\t", ledger->entries[i][j]);
      printf("%s", ledger->entries[NFIELDS - 1][j]); 
      printf("\n");     
    }
    
    printf("\nNAMES %d\n\n", test);
    get_names(ledger);
    
    printf("credits: ");
    for(i = 0; i < ledger->ncredits; ++i)
      printf("_%s ", ledger->credits[i]);
     printf("\n\n");  
    
    printf("\n\nbanks\n\n");    
    for(i = 0; i < ledger->nbanks; ++i){
      printf("_%s | ", ledger->banks[i]);
      for(j = 0; j < ledger->npartitions[i]; ++j)
        printf("_%s ", ledger->partitions[i][j]);    
             printf("\n");     
    }
     printf("\n\n");   
      
    free_ledger(ledger);
  }  

  for(test = 0; test < ntests; ++test)
    free(strs[test]);
  free(strs);

  return 0;
}
