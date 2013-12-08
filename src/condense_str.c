/***
 *** @file condense_str.c
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

void condense_str(char **s){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  condense(&ledger);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
} 
