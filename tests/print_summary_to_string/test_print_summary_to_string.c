#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L2 "../data/ledgers/empty.txt"
#define L3 "../data/ledgers/basic.txt"

int main(){
  Ledger *ledger = NULL;
  char *s;
  
  printf("\n----\nRET = %d\n---\n", print_summary_to_string(ledger, &s));
  printf("%s", s);  
  if(s != NULL){
    free(s);
    s = NULL;
  }
    
  new_ledger(&ledger);
  printf("\n----\nRET = %d\n---\n", print_summary_to_string(ledger, &s));
  free_ledger(&ledger);
  printf("%s", s);  
  if(s != NULL){
    free(s);
    s = NULL;
  }
  
  new_ledger(&ledger);
  get_entries_from_filename(ledger, L2); 
  get_names(ledger);
  printf("\n----\nRET = %d\n---\n", print_summary_to_string(ledger, &s));
  free_ledger(&ledger); 
  printf("%s", s);  
  if(s != NULL){
    free(s);
    s = NULL;
  }

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L2); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L2\n---\n", print_summary_to_string(ledger, &s));
  free_ledger(&ledger);
  printf("%s", s);  
  if(s != NULL){
    free(s);
    s = NULL;
  }
  
  new_ledger(&ledger);    
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  printf("\n----\nRET = %d\n---\n", print_summary_to_string(ledger, &s));
  free_ledger(&ledger); 
  printf("%s", s);  
  if(s != NULL){
    free(s);
    s = NULL;
  }

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_string(ledger, &s));
  free_ledger(&ledger);
  printf("%s", s);  
  if(s != NULL){
    free(s);
    s = NULL;
  } 
  
  return 0;
}
