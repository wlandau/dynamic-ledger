/***
 *** @file print_summary_to_stream.c
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

err_t print_summary_to_stream(Ledger *ledger, FILE *fp){ 
  int i, j, l0, l1, l2, any = 0, anyp = 0;

  if(ledger == NULL || fp == NULL)
    return LFAILURE;
    
  if(ledger->credit_totals == NULL || 
     ledger->bank_totals == NULL || 
     ledger->partition_totals == NULL)
     return LFAILURE;  

  fprintf(fp, "%s", NORMAL_COLOR);

  for(i = 0; i < ledger->ncredits; ++i){
    l0 = (abs(ledger->credit_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->credit_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->credit_totals[i][I_CLEARED]) > EPS);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credits[i]))
        fprintf(fp,"\nCredit account: %s\n\n", ledger->credits[i]);
      else
        fprintf(fp,"\nCredit account with no name:\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", 
                  color(ledger->credit_totals[i][I_NOT_THERE_YET]), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", 
                  color(ledger->credit_totals[i][I_PENDING]), 
                  ledger->credit_totals[i][I_PENDING], NORMAL_COLOR);
        fprintf(fp, "\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", 
                color(ledger->credit_totals[i][I_CLEARED]),
                ledger->credit_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  color(ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED]),
                  ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED],
                  NORMAL_COLOR);
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->credit_totals[i][I_OVERALL_BAL]),
                ledger->credit_totals[i][I_OVERALL_BAL], NORMAL_COLOR);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->credit_totals[i][I_OVERALL_BAL]), 
                ledger->credit_totals[i][I_OVERALL_BAL], NORMAL_COLOR); 
        fprintf(fp,"                                All charges cleared.\n");
      }
    }
  }
          
  for(i = 0; i < ledger->nbanks; ++i){
    l0 = (abs(ledger->bank_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->bank_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->bank_totals[i][I_CLEARED]) > EPS); 
  
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->banks[i]))
        fprintf(fp,"\nBank account: %s\n\n", ledger->banks[i]);
      else 
        fprintf(fp,"\nBank account with no name\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", 
                  color(ledger->bank_totals[i][I_NOT_THERE_YET]),
                  ledger->bank_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", 
                  color(ledger->bank_totals[i][I_PENDING]), 
                  ledger->bank_totals[i][I_PENDING], NORMAL_COLOR); 
        fprintf(fp,"\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", 
                color(ledger->bank_totals[i][I_CLEARED]),
                ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  color(ledger->bank_totals[i][I_PENDING] 
                + ledger->bank_totals[i][I_CLEARED]),
                  ledger->bank_totals[i][I_PENDING] 
                + ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->bank_totals[i][I_OVERALL_BAL]),
                ledger->bank_totals[i][I_OVERALL_BAL], NORMAL_COLOR);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->bank_totals[i][I_OVERALL_BAL]),
                ledger->bank_totals[i][I_OVERALL_BAL], NORMAL_COLOR);
        fprintf(fp,"                                All charges cleared.\n");
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartitions[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > EPS){
        if(strlen(ledger->partitions[i][j])){
          if(!anyp){
            fprintf(fp,"\n          Partitions:\n");
            ++anyp;
          }
          fprintf(fp,"%s%30.2f%s  %s\n", color(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], NORMAL_COLOR, ledger->partitions[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][I_CLEARED]) > EPS){
          if(!j) fprintf(fp, "\n");
          fprintf(fp,"%s%30.2f%s  unpartitioned\n", color(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], NORMAL_COLOR);
        }
      } 
  }
  
  if(any)
    fprintf(fp,"\n");
    
  return LSUCCESS;
}

