/***
 *** @file print_summary_to_string.c
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

char *print_summary_to_string(Ledger *ledger){
  int i, j, l0, l1, l2, any = 0, anyp = 0;
  
  char *s;

  if(ledger == NULL)
    return NULL;
    
  s = calloc(ledger->nrows * NFIELDS * ENTRYSIZE, sizeof(char));

  for(i = 0; i < ledger->ncredits; ++i){
    l0 = (abs(ledger->credit_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->credit_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->credit_totals[i][I_CLEARED]) > EPS);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credits[i]))
        sprintf(s,"%s\nCredit account: %s\n\n", s, ledger->credits[i]);
      else
        sprintf(s,"%s\nCredit account with no name:\n\n", s);
 
      if(l0 || l1){
      
        sprintf(s,"%s          Delayed money:\n",s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, 
                  color(ledger->credit_totals[i][I_NOT_THERE_YET]), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n", s, 
                  color(ledger->credit_totals[i][I_PENDING]), 
                  ledger->credit_totals[i][I_PENDING], NORMAL_COLOR);

        sprintf(s, "%s\n          Balances:\n", s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, 
                color(ledger->credit_totals[i][I_CLEARED]),
                ledger->credit_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  color(ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED]),
                  ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED],
                  NORMAL_COLOR);
        sprintf(s,"%s%s%30.2f%s  true balance\n",s, 
                color(ledger->credit_totals[i][I_OVERALL_BAL]),
                ledger->credit_totals[i][I_OVERALL_BAL], NORMAL_COLOR);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s, 
                color(ledger->credit_totals[i][I_OVERALL_BAL]), 
                ledger->credit_totals[i][I_OVERALL_BAL], NORMAL_COLOR); 
        sprintf(s,"%s                                All charges cleared.\n", s);
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
        sprintf(s,"%s\nBank account: %s\n\n", s, ledger->banks[i]);
      else 
        sprintf(s,"%s\nBank account with no name\n\n", s);
 
      if(l0 || l1){
        sprintf(s,"%s          Delayed money:\n", s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, color(ledger->bank_totals[i][I_NOT_THERE_YET]),
                  ledger->bank_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n",s, color(ledger->bank_totals[i][I_PENDING]), 
                  ledger->bank_totals[i][I_PENDING], NORMAL_COLOR); 
        sprintf(s,"%s\n          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, color(ledger->bank_totals[i][I_CLEARED]),
                ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  color(ledger->bank_totals[i][I_PENDING] + ledger->bank_totals[i][I_CLEARED]),
                  ledger->bank_totals[i][I_PENDING] + ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,color(ledger->bank_totals[i][I_OVERALL_BAL]),
                ledger->bank_totals[i][I_OVERALL_BAL], NORMAL_COLOR);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,color(ledger->bank_totals[i][I_OVERALL_BAL]),
                ledger->bank_totals[i][I_OVERALL_BAL], NORMAL_COLOR);
        sprintf(s,"%s                                All charges cleared.\n",s);
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartitions[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > EPS){
        if(strlen(ledger->partitions[i][j])){
          if(!anyp){
            sprintf(s,"%s\n          Partitions:\n",s);
            ++anyp;
          }
          sprintf(s,"%s%s%30.2f%s  %s\n",s, color(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], NORMAL_COLOR, ledger->partitions[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][I_CLEARED]) > EPS){
          if(!j) sprintf(s, "%s\n",s);
          sprintf(s,"%s%s%30.2f%s  unpartitioned\n",s, color(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], NORMAL_COLOR);
        }
      } 
  }
  
  if(any)
    sprintf(s,"%s\n",s);
    
  return s;
}

