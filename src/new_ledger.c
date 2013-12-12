/***
 *** @file new_ledger.c
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

Ledger *new_ledger(){
  Ledger *ledger = malloc(sizeof(Ledger));
  ledger->nrows = 0;
  ledger->nbanks = 0;
  ledger->ncredits = 0;
  ledger->banks = NULL;
  ledger->bank_totals = NULL;
  ledger->credits = NULL;
  ledger->credit_totals = NULL;
  ledger->entries= NULL;
  ledger->filename = NULL;
  ledger->npartitions = NULL;
  ledger->partitions = NULL;
  ledger->partition_totals = NULL;
  return ledger; 
}

