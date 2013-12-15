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
  char **partitions = NULL;
  int npartitions = 3, i;
  double *amounts = NULL;

  printf("TEST 1 RET = %d\n", repartition(ledger, "hi", partitions, amounts, npartitions, 1));

  amounts = malloc(npartitions * sizeof(double));
  amounts[0] = 30;
  amounts[1] = 30;
  amounts[2] = 40;
  
  partitions = malloc(npartitions * sizeof(char*));
  for(i = 0; i < npartitions; ++i)
    partitions[i] = malloc(ENTRYSIZE * sizeof(char));
    
  strcpy(partitions[0], "wheedle");
  strcpy(partitions[1], "goofus");
  strcpy(partitions[2], "poofdoofus");

  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_verbose(ledger, stdout);  
 
  printf("TEST 1 RET = %d\n", repartition(ledger, "RABIES", partitions, amounts, npartitions, 1));
  printf("TEST 2 RET = %d\n", repartition(ledger, "cp", partitions, amounts, npartitions, 1));

  print_ledger_verbose(ledger, stdout);
  strcpy(partitions[2], NIL);
  printf("TEST 3 RET = %d\n", repartition(ledger, "cp", partitions, amounts, npartitions, 1));
  print_ledger_verbose(ledger, stdout);
  


  strcpy(partitions[0], "one");
  strcpy(partitions[1], "two");
  strcpy(partitions[2], "three");
  
  amounts[0] = 659.12;
  amounts[1] = 5000;
  amounts[2] = 4999.99; 
  
  printf("TEST 4 RET = %d\n", repartition(ledger, "cps", partitions, amounts, npartitions, 0));

  amounts[2] = 5000;
  printf("TEST 5 RET = %d\n", repartition(ledger, "cps", partitions, amounts, npartitions, 0));
  print_ledger_verbose(ledger, stdout);

  free_ledger(&ledger);

  get_ledger(&ledger, "../data/ledgers/empty.txt", NULL, NULL);
  amounts[0] = 30;
  amounts[1] = -15;
  amounts[2] = -15;

  printf("TEST 6 RET = %d\n", repartition(ledger, NIL, partitions, amounts, npartitions, 1));
  print_ledger_verbose(ledger, stdout);

  printf("TEST 7 RET = %d\n", repartition(ledger, NIL, partitions, amounts, npartitions, 0));
  print_ledger_verbose(ledger, stdout);


  for(i = 0; i < npartitions; ++i)
    free(partitions[i]);
  free(partitions);

  free(amounts);

  return 0;
}
