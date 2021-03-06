/**
 * @file        print_summary_to_string.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */
 
#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Print a summary of a Ledger object to a file stream.
 *          Set usecolor to 1 to print with command line interface 
 *          color codes defined in the Printing_Macros module. 
 *          Set usecolor to 0 to not use these color codes.
 */
err_t print_summary_to_string(Ledger *ledger, char **s, int usecolor){
  int i, j, l0, l1, l2, any = 0, anyp = 0, nullp;
  char norm[64]; 

  /* Check for bad input */
    
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
  
  /* Allocate space for string and test if calloc worked */
    
  *s = calloc((ledger->nrows + 1) * NFIELDS * LINESIZE, sizeof(char));
  if(*s == NULL){
    fprintf(stderr, "Error: calloc failed.\n");
    return LFAILURE;
  }

  /* Print summary to string */

  strncpy(norm, usecolor ? NORMAL_COLOR : "", 63 * sizeof(char));

  /* Print summaries of credit accounts */

  for(i = 0; i < ledger->ncredits; ++i){
    l0 = (small_norm(ledger->credit_totals[i][I_NOT_THERE_YET]) == LNO);
    l1 = (small_norm(ledger->credit_totals[i][I_PENDING]) == LNO);
    l2 = (small_norm(ledger->credit_totals[i][I_CLEARED]) == LNO);
 
    if(l0 || l1 || l2 || (PRINT_EMPTY_ACCOUNTS && strlen(ledger->credits[i]))){
      ++any;
      if(strlen(ledger->credits[i]))
        snprintf(*s, LINESIZE * sizeof(char),"%s\nCredit account: %s\n\n", *s, ledger->credits[i]);
      else
        snprintf(*s, LINESIZE * sizeof(char),"%s\nCredit account with no name:\n\n", *s);
 
      if(l0 || l1){
      
        snprintf(*s, LINESIZE * sizeof(char),"%s          Delayed money:\n", *s);
        if(l0)
          snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  not arrived\n", *s, 
                  color(ledger->credit_totals[i][I_NOT_THERE_YET], usecolor), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], usecolor ? norm : ""); 
        if(l1)
          snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  pending\n", *s, 
                  color(ledger->credit_totals[i][I_PENDING], usecolor), 
                  ledger->credit_totals[i][I_PENDING], norm);

        snprintf(*s, LINESIZE * sizeof(char), "%s\n          Balances:\n", *s);
        snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  \"available\"\n", *s, 
                color(ledger->credit_totals[i][I_CLEARED], usecolor),
                ledger->credit_totals[i][I_CLEARED], norm);
        if(l1 && l0)
          snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  pending balance\n", *s,
                  color(ledger->credit_totals[i][I_PENDING_BAL], usecolor),
                  ledger->credit_totals[i][I_PENDING_BAL],
                  norm);
        snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  true balance\n", *s, 
                color(ledger->credit_totals[i][I_OVERALL_BAL], usecolor),
                ledger->credit_totals[i][I_OVERALL_BAL], norm);
      } else {
        snprintf(*s, LINESIZE * sizeof(char), "%s          Balances:\n", *s);
        snprintf(*s, LINESIZE * sizeof(char), "%s%s%30.2f%s  true balance\n", *s, 
                color(ledger->credit_totals[i][I_OVERALL_BAL], usecolor), 
                ledger->credit_totals[i][I_OVERALL_BAL], norm); 
        snprintf(*s, LINESIZE * sizeof(char), "%s                                All charges cleared.\n", *s);
      }
    }
  }     

  /* Print summaries of bank accounts */
        
  for(i = 0; i < ledger->nbanks; ++i){
    l0 = (small_norm(ledger->bank_totals[i][I_NOT_THERE_YET]) == LNO);
    l1 = (small_norm(ledger->bank_totals[i][I_PENDING]) == LNO);
    l2 = (small_norm(ledger->bank_totals[i][I_CLEARED]) == LNO) ||      
         filled_partitions(ledger, i); 
  
    if(l0 || l1 || l2 || (PRINT_EMPTY_ACCOUNTS && strlen(ledger->banks[i]))){
      ++any;
      if(strlen(ledger->banks[i]))
        snprintf(*s, LINESIZE * sizeof(char),"%s\nBank account: %s\n\n", *s, ledger->banks[i]);
      else 
        snprintf(*s, LINESIZE * sizeof(char),"%s\nBank account with no name\n\n", *s);
 
      if(l0 || l1){
        snprintf(*s, LINESIZE * sizeof(char),"%s          Delayed money:\n", *s);
        if(l0)
          snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  not arrived\n", *s, 
                  color(ledger->bank_totals[i][I_NOT_THERE_YET], usecolor),
                  ledger->bank_totals[i][I_NOT_THERE_YET], norm); 
        if(l1)
          snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  pending\n",*s, 
                  color(ledger->bank_totals[i][I_PENDING], usecolor), 
                  ledger->bank_totals[i][I_PENDING], norm); 
        snprintf(*s, LINESIZE * sizeof(char), "%s\n          Balances:\n", *s);
        snprintf(*s, LINESIZE * sizeof(char), "%s%s%30.2f%s  \"available\"\n", *s, 
                color(ledger->bank_totals[i][I_CLEARED], usecolor),
                ledger->bank_totals[i][I_CLEARED], norm);
        if(l1 && l0)
          snprintf(*s, LINESIZE * sizeof(char), "%s%s%30.2f%s  pending balance\n", *s,
                  color(ledger->bank_totals[i][I_PENDING_BAL], usecolor),
                  ledger->bank_totals[i][I_PENDING_BAL], norm);
        snprintf(*s, LINESIZE * sizeof(char), "%s%s%30.2f%s  true balance\n", *s, 
                color(ledger->bank_totals[i][I_OVERALL_BAL], usecolor),
                ledger->bank_totals[i][I_OVERALL_BAL], norm);
      } else {
        snprintf(*s, LINESIZE * sizeof(char), "%s          Balances:\n", *s);
        snprintf(*s, LINESIZE * sizeof(char), "%s%s%30.2f%s  true balance\n", *s,
                color(ledger->bank_totals[i][I_OVERALL_BAL], usecolor),
                ledger->bank_totals[i][I_OVERALL_BAL], norm);
        snprintf(*s, LINESIZE * sizeof(char), "%s                                All charges cleared.\n", *s);
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartitions[i]; ++j)
      if(small_norm(ledger->partition_totals[i][j]) == LNO){
        if(strlen(ledger->partitions[i][j])){
          if(!anyp){
            snprintf(*s, LINESIZE * sizeof(char),"%s\n          Partitions:\n", *s);
            ++anyp;
          }
          snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  %s\n", *s, color(ledger->partition_totals[i][j], usecolor), 
                  ledger->partition_totals[i][j], norm, ledger->partitions[i][j]);
        }
      }
      
    nullp = which(ledger->partitions[i], NIL, ledger->npartitions[i]);
    if(anyp && (small_norm(ledger->partition_totals[i][nullp]) == LNO))
      snprintf(*s, LINESIZE * sizeof(char),"%s%s%30.2f%s  unpartitioned\n", *s,
                  color(ledger->partition_totals[i][nullp], usecolor),
                  ledger->partition_totals[i][nullp], norm);
  }
  
  /* Strip the output string of trailing whitespace */
  
  if(str_strip(*s) == LFAILURE)
    return LFAILURE;
  
  /* If all accounts are empty, say so */
  
  if(any)
    snprintf(*s, LINESIZE * sizeof(char), "%s\n\n", *s);
  else
    printf("All accounts are empty.\n");
 
  return LSUCCESS;
}

