#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char c;
  
  c = '\t';
  printf("%c\t%d\n", c, row_delim_char(c));
  
  c = '	'; /* tab */
  printf("%c\t%d\n", c, row_delim_char(c));
 
  c = '\n';
  printf("%c\t%d\n", c, row_delim_char(c)); 
 
  c = '\r';
  printf("%c\t%d\n", c, row_delim_char(c));
  
  c = 't';
  printf("%c\t%d\n", c, row_delim_char(c));   
     
  c = 'r';
  printf("%c\t%d\n", c, row_delim_char(c));  

  c = 'n';
  printf("%c\t%d\n", c, row_delim_char(c));  
     
  c = 's';
  printf("%c\t%d\n", c, row_delim_char(c));  
     
  c = ' ';
  printf("%c\t%d\n", c, row_delim_char(c));  

  c = '\0';
  printf("%c\t%d\n", c, row_delim_char(c));  

  return 0;
}
