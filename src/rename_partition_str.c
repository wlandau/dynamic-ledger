/***
 *** @file rename_partition_str.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rename_partition_str(char **s, char *bank, char *from, char *to){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  rename_partition(ledger, bank, from, to);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}
