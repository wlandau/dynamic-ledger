/***
 *** @file print_summary_to_string.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *print_summary_to_string(Ledger *ledger){
  int i, j, l0, l1, l2, any = 0, anyp = 0;
  
  char *s;

  if(ledger == NULL)
    return NULL;
    
  s = calloc(ledger->n * NFIELDS * ENTRYSIZE, sizeof(char));

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->credit_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->credit_totals[i][I_CLEARED]) > EPS);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credit[i]))
        sprintf(s,"%s\nCredit account: %s\n\n", s, ledger->credit[i]);
      else
        sprintf(s,"%s\nCredit account with no name:\n\n", s);
 
      if(l0 || l1){
      
        sprintf(s,"%s          Delayed money:\n",s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, 
                  get_color(ledger->credit_totals[i][I_NOT_THERE_YET]), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n", s, 
                  get_color(ledger->credit_totals[i][I_PENDING]), 
                  ledger->credit_totals[i][I_PENDING], NORMAL_COLOR);

        sprintf(s, "%s\n          Balances:\n", s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, 
                get_color(ledger->credit_totals[i][I_CLEARED]),
                ledger->credit_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  get_color(ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED]),
                  ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED],
                  NORMAL_COLOR);
        sprintf(s,"%s%s%30.2f%s  true balance\n",s, 
                get_color(ledger->credit_totals[i][I_OVERALL]),
                ledger->credit_totals[i][I_OVERALL], NORMAL_COLOR);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s, 
                get_color(ledger->credit_totals[i][I_OVERALL]), 
                ledger->credit_totals[i][I_OVERALL], NORMAL_COLOR); 
        sprintf(s,"%s                                All charges cleared.\n", s);
      }
    }
  }     
          
  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->bank_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->bank_totals[i][I_CLEARED]) > EPS); 
  
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->bank[i]))
        sprintf(s,"%s\nBank account: %s\n\n", s, ledger->bank[i]);
      else 
        sprintf(s,"%s\nBank account with no name\n\n", s);
 
      if(l0 || l1){
        sprintf(s,"%s          Delayed money:\n", s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, get_color(ledger->bank_totals[i][I_NOT_THERE_YET]),
                  ledger->bank_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n",s, get_color(ledger->bank_totals[i][I_PENDING]), 
                  ledger->bank_totals[i][I_PENDING], NORMAL_COLOR); 
        sprintf(s,"%s\n          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, get_color(ledger->bank_totals[i][I_CLEARED]),
                ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  get_color(ledger->bank_totals[i][I_PENDING] + ledger->bank_totals[i][I_CLEARED]),
                  ledger->bank_totals[i][I_PENDING] + ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,get_color(ledger->bank_totals[i][I_OVERALL]),
                ledger->bank_totals[i][I_OVERALL], NORMAL_COLOR);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,get_color(ledger->bank_totals[i][I_OVERALL]),
                ledger->bank_totals[i][I_OVERALL], NORMAL_COLOR);
        sprintf(s,"%s                                All charges cleared.\n",s);
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > EPS){
        if(strlen(ledger->partition[i][j])){
          if(!anyp){
            sprintf(s,"%s\n          Partitions:\n",s);
            ++anyp;
          }
          sprintf(s,"%s%s%30.2f%s  %s\n",s, get_color(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], NORMAL_COLOR, ledger->partition[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][I_CLEARED]) > EPS){
          if(!j) sprintf(s, "%s\n",s);
          sprintf(s,"%s%s%30.2f%s  unpartitioned\n",s, get_color(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], NORMAL_COLOR);
        }
      } 
  }
  
  if(any)
    sprintf(s,"%s\n",s);
    
  return s;
}

