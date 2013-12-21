#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  int i, j, ret;
  Ledger *ledger = NULL;
  
  ret = alloc_entries(ledger);
  printf("\n----\n1 RETURN VALUE = %d\n---\n", ret);

  new_ledger(&ledger);
  ret = alloc_entries(ledger);
  printf("\n----\n2 RETURN VALUE = %d\n---\n", ret);
  
  ledger->nrows = 4;
  ret = alloc_entries(ledger);
  printf("\n----\n3 RETURN VALUE = %d\n---\n", ret);
  
  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < ledger->nrows; ++j)
      printf("e[%d][%d]=%s ", i, j, ledger->entries[i][j]);
    printf("\n");
  }
  
  free_ledger(&ledger);
  return 0;
}
