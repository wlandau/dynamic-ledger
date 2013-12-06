/***
 *** @file trim_ledger.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim_ledger(Ledger *ledger){
  int i; 

  if(ledger == NULL)
    return;

  for(i = (ledger->n - 1); i >= 0; --i)
    if(abs(atof(ledger->text_content[AMOUNT][i])) < EPS)
      remove_row(ledger, i);
}
