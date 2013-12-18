/***
 *** @file print_summary_to_stream.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t print_summary_to_stream(Ledger *ledger, FILE *fp, int usecolor){ 
  int i, j, l0, l1, l2, any = 0, anyp = 0, nullp;
  char norm[64];

  if(fp == NULL)
    return LFAILURE;
    
  if(ledger == NULL){
    printf("Ledger is empty.\n");
    return LFAILURE;
  }  
    
  if(ledger->nrows < 1){
    printf("Ledger is empty.\n");
    return LFAILURE;
  }  
    
  if(untotaled(ledger) == LYES){
     printf("Account totals have not been calculated. Ledger may be empty.\n");  
     return LFAILURE; 
  } 

  strcpy(norm, usecolor ? NORMAL_COLOR : "");
  fprintf(fp, "%s", norm);

  for(i = 0; i < ledger->ncredits; ++i){
    l0 = (small_norm(ledger->credit_totals[i][I_NOT_THERE_YET]) == LNO);
    l1 = (small_norm(ledger->credit_totals[i][I_PENDING]) == LNO);
    l2 = (small_norm(ledger->credit_totals[i][I_CLEARED]) == LNO);      
 
    if(l0 || l1 || l2 || (PRINT_EMPTY_ACCOUNTS && strlen(ledger->credits[i]))){
      ++any;
      if(strlen(ledger->credits[i]))
        fprintf(fp,"\nCredit account: %s\n\n", ledger->credits[i]);
      else
        fprintf(fp,"\nCredit account with no name:\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", 
                  color(ledger->credit_totals[i][I_NOT_THERE_YET], usecolor), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], norm); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", 
                  color(ledger->credit_totals[i][I_PENDING], usecolor), 
                  ledger->credit_totals[i][I_PENDING], norm);
        fprintf(fp, "\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", 
                color(ledger->credit_totals[i][I_CLEARED], usecolor),
                ledger->credit_totals[i][I_CLEARED], norm);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  color(ledger->credit_totals[i][I_PENDING_BAL], usecolor),
                  ledger->credit_totals[i][I_PENDING_BAL], norm);
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->credit_totals[i][I_OVERALL_BAL], usecolor),
                ledger->credit_totals[i][I_OVERALL_BAL], norm);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->credit_totals[i][I_OVERALL_BAL], usecolor), 
                ledger->credit_totals[i][I_OVERALL_BAL], norm); 
        fprintf(fp,"                                All charges cleared.\n");
      }
    }
  }
          
  for(i = 0; i < ledger->nbanks; ++i){
    l0 = (small_norm(ledger->bank_totals[i][I_NOT_THERE_YET]) == LNO);
    l1 = (small_norm(ledger->bank_totals[i][I_PENDING]) == LNO);
    l2 = (small_norm(ledger->bank_totals[i][I_CLEARED]) == LNO) || 
         filled_partitions(ledger, i);
  
    if(l0 || l1 || l2 || (PRINT_EMPTY_ACCOUNTS && strlen(ledger->banks[i]))){
      ++any;
      if(strlen(ledger->banks[i]))
        fprintf(fp,"\nBank account: %s\n\n", ledger->banks[i]);
      else 
        fprintf(fp,"\nBank account with no name\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", 
                  color(ledger->bank_totals[i][I_NOT_THERE_YET], usecolor),
                  ledger->bank_totals[i][I_NOT_THERE_YET], norm); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", 
                  color(ledger->bank_totals[i][I_PENDING], usecolor), 
                  ledger->bank_totals[i][I_PENDING], norm); 
        fprintf(fp,"\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", 
                color(ledger->bank_totals[i][I_CLEARED], usecolor),
                ledger->bank_totals[i][I_CLEARED], norm);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  color(ledger->bank_totals[i][I_PENDING_BAL], usecolor),
                  ledger->bank_totals[i][I_PENDING_BAL], norm);
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->bank_totals[i][I_OVERALL_BAL], usecolor),
                ledger->bank_totals[i][I_OVERALL_BAL], norm);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                color(ledger->bank_totals[i][I_OVERALL_BAL], usecolor),
                ledger->bank_totals[i][I_OVERALL_BAL], norm);
        fprintf(fp,"                                All charges cleared.\n");
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartitions[i]; ++j)
      if(small_norm(ledger->partition_totals[i][j]) == LNO){
        if(strlen(ledger->partitions[i][j])){
          if(!anyp){
            fprintf(fp,"\n          Partitions:\n");
            ++anyp;
          }
          fprintf(fp,"%s%30.2f%s  %s\n", color(ledger->partition_totals[i][j], usecolor), 
                  ledger->partition_totals[i][j], norm, ledger->partitions[i][j]);
        }
      }
      
    nullp = which(ledger->partitions[i], NIL, ledger->npartitions[i]);
    if(anyp && (small_norm(ledger->partition_totals[i][nullp]) == LNO))
      fprintf(fp,"%s%30.2f%s  unpartitioned\n", 
                  color(ledger->partition_totals[i][nullp], usecolor),
                  ledger->partition_totals[i][nullp], norm);
  }
  
  if(any)
    fprintf(fp,"\n");
  else
    printf("Ledger is empty.\n");
    
  return LSUCCESS;
}

