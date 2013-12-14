#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L0 ""
#define L1 "hi\th i \n"
#define L2 "hi\th i\nr1f1\tr1f2"
#define L3 "hi	h i \nr1f1	r1f2 \nr2f1	rt2f2"
#define L4 "hi\th i	\nr1f1\tr1f2"
#define L5 "hi\th i	\nr1f1\tr1f2\nr2f1\tr2f2"
#define L6 "amount	status	credit	bank	partition	description\n-27.58	cp	ch	cp	a	hyvee-12/10/13\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed"
#define L7 "\n-27.58	cp	ch	cp	a	hyvee-12/10/13\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed\n"
#define L8 "-27.58	cp	ch	cp	a	hyvee-12/10/13\tgagagadada\n-6.76		ch	cp	a	hyvee-1711902571-65.98\tgagagadada\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed\n"
#define L9 "-27.58	cp	ch	cp	a	hyvee-12/10/13abcdefghijklmnopqrstuvwxyz__hyvee-12/10/13abcdefghijklmnopqrstuvwxyz__hyvee-12/10/13abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__\tgagagadada\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed\n"


#define F "../data/ledgers/bad.txt"

int main(){
  int i, j, char_index, field, row, test, ntests = 10;
  Ledger *ledger;
  char **strs;

  strs = malloc(ntests * sizeof(char*));
  for(i = 0; i < ntests; ++i)
    strs[i] = calloc(2000, sizeof(char));

  strcpy(strs[0], L0);
  strcpy(strs[1], L1);
  strcpy(strs[2], L2);
  strcpy(strs[3], L3);
  strcpy(strs[4], L4);
  strcpy(strs[5], L5);
  strcpy(strs[6], L6);
  strcpy(strs[7], L7);
  strcpy(strs[8], L8);
  strcpy(strs[9], L9);
    
  for(test = 0; test < ntests; ++test){
    printf("\n--------\nTEST %d\n", test);
    new_ledger(&ledger);
    ledger->nrows = 1;
    for(i = 0; i < strlen(strs[test]); ++i)
      if(strs[test][i] == '\n' || strs[test][i] == '\r')
        ++ledger->nrows;
    alloc_entries(ledger);
    
    char_index = 0;
    field = 0;
    row = 0; 
 
    for(j = 0; j < strlen(strs[test]); ++i){
      parse_char(ledger, strs[test][j], &char_index, &field, &row);
      ++j;
    }
    
    printf("\nENTRIES %d\n\n", test);
 
 
    for(j = 0; j < ledger->nrows; ++j){   
      for(i = 0; i < NFIELDS - 1; ++i)
        printf("%s\t", ledger->entries[i][j]);
      printf("%s", ledger->entries[NFIELDS - 1][j]); 
      printf("\n");     
    }
    
    free_ledger(&ledger);
  }  

  for(test = 0; test < ntests; ++test)
    free(strs[test]);
  free(strs);

  return 0;
}
