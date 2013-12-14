/***
 *** @file rename_credit_str.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

void rename_credit_str(char **s, char *from, char *to){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  get_ledger(&ledger, NULL, NULL, *s);
  
  if(ledger == NULL)
    return;
  
  rename_credit(ledger, from, to);
  s2 = print_ledger_to_string(ledger);
  free_ledger(&ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}
