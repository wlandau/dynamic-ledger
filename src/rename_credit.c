/***
 *** @file rename_credit.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rename_credit(Ledger *ledger, char *from, char *to){
  int i;

  if(ledger == NULL)
    return;

  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[CREDIT][i], from))
      strcpy(ledger->text_content[CREDIT][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}
