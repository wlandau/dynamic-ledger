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
  
  printf("\n----\nRET = %d\n---\n", print_summary_to_stream(ledger, stdout, 1));
    
  new_ledger(&ledger);
  printf("\n----\nRET = %d\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L2); 
  get_names(ledger);
  printf("\n----\nRET = %d\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger); 

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L2); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L2\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);

  new_ledger(&ledger);    
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  printf("\n----\nRET = %d\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger); 

  new_ledger(&ledger);
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);
  
  
  new_ledger(&ledger);
  get_entries_from_filename(ledger, L3); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_stream(ledger, stdout, 0));
  free_ledger(&ledger);

  new_ledger(&ledger);
  get_entries_from_filename(ledger, "../data/ledgers/small.txt"); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);
  
  new_ledger(&ledger);
  get_entries_from_filename(ledger, "../data/ledgers/small2.txt"); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);

  printf("empty..\n");
  new_ledger(&ledger);
  get_entries_from_filename(ledger, "../data/ledgers/empty.txt"); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);
  
  printf("nonnull..\n");
  new_ledger(&ledger);
  get_entries_from_filename(ledger, "../data/ledgers/nonnull.txt"); 
  get_names(ledger);
  get_totals(ledger);
  printf("\n----\nRET = %d L3\n---\n", print_summary_to_stream(ledger, stdout, 1));
  free_ledger(&ledger);

  return 0;
}
