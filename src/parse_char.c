/***
 *** @file parse_char.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

err_t parse_char(Ledger *ledger, char c, int *char_index, int *field, int *row){
  if(col_delim_char(c)){
    *char_index = 0;
    ++(*field); 
  } else if(row_delim_char(c)){
    *char_index = 0;
    *field = 0;
    ++(*row); 
  } else if(*field < NFIELDS && *char_index < ENTRYSIZE - 1){
    ledger->entries[*field][*row][*char_index] = c;
    ++(*char_index); 
  } 
  
  return LSUCCESS;
}
