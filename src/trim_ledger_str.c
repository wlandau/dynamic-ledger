/***
 *** @file trim_ledger_str.c
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

void trim_ledger_str(char **s){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  get_ledger(&ledger, NULL, NULL, *s);
  
  if(ledger == NULL)
    return;
  
  trim_ledger(ledger);
  print_ledger_to_string(ledger, &s2);
  free_ledger(&ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
} 
