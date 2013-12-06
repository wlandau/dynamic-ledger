/***
 *** @file print_ledger_to_string.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *print_ledger_to_string(Ledger *ledger){
  char *s, entry[ENTRYSIZE], 
        header[] = "amount\tstatus\tcredit\tbank\tpartition\tdescription\n"; 
  int i, j, n = 1;
  
  if(ledger == NULL)
    return NULL;
  
  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < ledger->n; ++j){
      n += strlen(ledger->text_content[i][j]) + 1;
    }
  }
  
  s = calloc(n + strlen(header), sizeof(char));
  strcat(s, header);
  for(j = 0; j < ledger->n; ++j){
    strcat(s, ledger->text_content[AMOUNT][j]);
    
    for(i = 1; i < NFIELDS; ++i){
      strcat(s, "\t");
      
      if(strlen(ledger->text_content[i][j])){
        sprintf(entry, "%s", ledger->text_content[i][j]);
        
        str_strip(entry);
        strcat(s, entry);
      }
    }
    
    strcat(s, "\n"); 
  }
  return s;
}
