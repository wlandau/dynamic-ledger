/***
 *** @file untotaled.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>


bool_t untotaled(Ledger *ledger){
  if(ledger == NULL)
    return LYES;
    
  if(ledger->banks == NULL || ledger->credits == NULL || ledger->partitions == NULL ||
     !ledger->nbanks || !ledger->ncredits || ledger->npartitions == NULL)  
    return LYES;
  
  if(ledger->bank_totals == NULL || ledger->credit_totals == NULL || 
     ledger->partition_totals == NULL)
    return LYES;
    
  return LNO;
}
