#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

void parse_char(Ledger *ledger, char c, int *char_index, int *field, int *row){
  if(c == '\t'){
    *char_index = 0;
    ++(*field); 
  } else if(c == '\n' || c == '\r'){
    *char_index = 0;
    *field = 0;
    ++(*row); 
  } else if(*field < NFIELDS && *char_index < ENTRYSIZE - 1){
    ledger->entries[*field][*row][*char_index] = c;
    ++(*char_index); 
  }
}
