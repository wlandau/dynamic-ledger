/***
 *** @file print_summary_to_string.c
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

err_t print_summary_to_string(Ledger *ledger, char **s, int usecolor){
  int i, j, l0, l1, l2, any = 0, anyp = 0, nullp;
  char norm[64]; 

  if(ledger == NULL)
    return LFAILURE;
 
  if(untotaled(ledger) == LYES)
     return LFAILURE; 
    
  *s = calloc(ledger->nrows * NFIELDS * ENTRYSIZE, sizeof(char));
  strcpy(norm, usecolor ? NORMAL_COLOR : "");

  for(i = 0; i < ledger->ncredits; ++i){
    l0 = (small_norm(ledger->credit_totals[i][I_NOT_THERE_YET]) == LNO);
    l1 = (small_norm(ledger->credit_totals[i][I_PENDING]) == LNO);
    l2 = (small_norm(ledger->credit_totals[i][I_CLEARED]) == LNO);
 
    if(l0 || l1 || l2 || (PRINT_EMPTY_ACCOUNTS && strlen(ledger->credits[i]))){
      ++any;
      if(strlen(ledger->credits[i]))
        sprintf(*s,"%s\nCredit account: %s\n\n", *s, ledger->credits[i]);
      else
        sprintf(*s,"%s\nCredit account with no name:\n\n", *s);
 
      if(l0 || l1){
      
        sprintf(*s,"%s          Delayed money:\n", *s);
        if(l0)
          sprintf(*s,"%s%s%30.2f%s  not arrived\n", *s, 
                  color(ledger->credit_totals[i][I_NOT_THERE_YET], usecolor), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], usecolor ? norm : ""); 
        if(l1)
          sprintf(*s,"%s%s%30.2f%s  pending\n", *s, 
                  color(ledger->credit_totals[i][I_PENDING], usecolor), 
                  ledger->credit_totals[i][I_PENDING], norm);

        sprintf(*s, "%s\n          Balances:\n", *s);
        sprintf(*s,"%s%s%30.2f%s  \"available\"\n", *s, 
                color(ledger->credit_totals[i][I_CLEARED], usecolor),
                ledger->credit_totals[i][I_CLEARED], norm);
        if(l1 && l0)
          sprintf(*s,"%s%s%30.2f%s  pending balance\n", *s,
                  color(ledger->credit_totals[i][I_PENDING_BAL], usecolor),
                  ledger->credit_totals[i][I_PENDING_BAL],
                  norm);
        sprintf(*s,"%s%s%30.2f%s  true balance\n", *s, 
                color(ledger->credit_totals[i][I_OVERALL_BAL], usecolor),
                ledger->credit_totals[i][I_OVERALL_BAL], norm);
      } else {
        sprintf(*s, "%s          Balances:\n", *s);
        sprintf(*s, "%s%s%30.2f%s  true balance\n", *s, 
                color(ledger->credit_totals[i][I_OVERALL_BAL], usecolor), 
                ledger->credit_totals[i][I_OVERALL_BAL], norm); 
        sprintf(*s, "%s                                All charges cleared.\n", *s);
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
        sprintf(*s,"%s\nBank account: %s\n\n", *s, ledger->banks[i]);
      else 
        sprintf(*s,"%s\nBank account with no name\n\n", *s);
 
      if(l0 || l1){
        sprintf(*s,"%s          Delayed money:\n", *s);
        if(l0)
          sprintf(*s,"%s%s%30.2f%s  not arrived\n", *s, 
                  color(ledger->bank_totals[i][I_NOT_THERE_YET], usecolor),
                  ledger->bank_totals[i][I_NOT_THERE_YET], norm); 
        if(l1)
          sprintf(*s,"%s%s%30.2f%s  pending\n",*s, 
                  color(ledger->bank_totals[i][I_PENDING], usecolor), 
                  ledger->bank_totals[i][I_PENDING], norm); 
        sprintf(*s, "%s\n          Balances:\n", *s);
        sprintf(*s, "%s%s%30.2f%s  \"available\"\n", *s, 
                color(ledger->bank_totals[i][I_CLEARED], usecolor),
                ledger->bank_totals[i][I_CLEARED], norm);
        if(l1 && l0)
          sprintf(*s, "%s%s%30.2f%s  pending balance\n", *s,
                  color(ledger->bank_totals[i][I_PENDING_BAL], usecolor),
                  ledger->bank_totals[i][I_PENDING_BAL], norm);
        sprintf(*s, "%s%s%30.2f%s  true balance\n", *s, 
                color(ledger->bank_totals[i][I_OVERALL_BAL], usecolor),
                ledger->bank_totals[i][I_OVERALL_BAL], norm);
      } else {
        sprintf(*s, "%s          Balances:\n", *s);
        sprintf(*s, "%s%s%30.2f%s  true balance\n", *s,
                color(ledger->bank_totals[i][I_OVERALL_BAL], usecolor),
                ledger->bank_totals[i][I_OVERALL_BAL], norm);
        sprintf(*s, "%s                                All charges cleared.\n", *s);
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartitions[i]; ++j)
      if(small_norm(ledger->partition_totals[i][j]) == LNO){
        if(strlen(ledger->partitions[i][j])){
          if(!anyp){
            sprintf(*s,"%s\n          Partitions:\n", *s);
            ++anyp;
          }
          sprintf(*s,"%s%s%30.2f%s  %s\n", *s, color(ledger->partition_totals[i][j], usecolor), 
                  ledger->partition_totals[i][j], norm, ledger->partitions[i][j]);
        }
      }
      
    nullp = which(ledger->partitions[i], NIL, ledger->npartitions[i]);
    if(anyp && (small_norm(ledger->partition_totals[i][nullp]) == LNO))
      sprintf(*s,"%s%s%30.2f%s  unpartitioned\n", *s,
                  color(ledger->partition_totals[i][nullp], usecolor),
                  ledger->partition_totals[i][nullp], norm);
  }
  
  str_strip(*s);  
  if(any)
    sprintf(*s, "%s\n\n", *s);
 
  return LSUCCESS;
}

