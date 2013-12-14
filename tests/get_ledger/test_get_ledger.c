#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define L0 "../data/ledgers/bad.txt"
#define L1 "../data/ledgers/bad2.txt"
#define L2 "../data/ledgers/bad3.txt"
#define L3 "../data/ledgers/basic.txt"
#define L4 "../data/ledgers/condensed.txt"
#define L5 "../data/ledgers/empty.txt"
#define L6 "../data/ledgers/example_ledger.txt"
#define L7 "../data/ledgers/just_bank.txt"
#define L8 "../data/ledgers/justcredit.txt"
#define L9 "../data/ledgers/nonnull.txt"
#define L10 "../data/ledgers/small.txt"



#define S0 ""
#define S1 "hi\th i \n"
#define S2 "hi\th i\nr1f1\tr1f2"
#define S3 "hi	h i \nr1f1	r1f2 \nr2f1	rt2f2"
#define S4 "hi\th i	\nr1f1\tr1f2"
#define S5 "hi\th i	\nr1f1\tr1f2\nr2f1\tr2f2"
#define S6 "amount	status	credit	bank	partition	description\n-27.58	cp	ch	cp	a	hyvee-12/10/13\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed"
#define S7 "-27.58	cp	ch	cp	a	hyvee-12/10/13\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed\n"
#define S8 "-27.58	cp	ch	cp	a	hyvee-12/10/13\tgagagadada\n-6.76	garbage	ch	cp	a	hyvee-1711902571-65.98\tgagagadada\n-30.adslfkj14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed\n"
#define S9 "-0.00	cp	ch	cp	a	hyvee-12/10/13abcdefghijklmnopqrstuvwxyz__hyvee-12/10/13abcdefghijklmnopqrstuvwxyz__hyvee-12/10/13abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__abcdefghijklmnopqrstuvwxyz__\tgagagadada\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed\n"
#define S10 "amount	status	credit	bank	partition	description\n-27.58	cp	ch	cp	a	hyvee-12/10/13\n350	n		cps		grandma\n-6.76		ch	cp	a	hyvee-1711902571-65.98\n-30.14		ch	cp	a	hyvee-1711902571-65.98\n-6.41		ch	cp	a	hyvee-1711902571-65.98\n-15.36		ch	cp	a	hyvee-1711902571-65.98\n-7.31		ch	cp	a	hyvee-1711902571-65.98\n305.26			cp	a	condensed\n112.21			cp	b	condensed\n256.03			cp	c	condensed\n138.33			cp	d	condensed\n90.00			cp	knee	condensed\n2114.56			cp	r	condensed\n3553.04			cps		condensed"



int main(){
  int i, j, test, ntests = 11;
  Ledger *ledger = NULL;
  FILE *fp;
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
  strcpy(strs[10], L10);
  
  
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("  FROM FILENAMES \n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");

  printf("\n--------\nTEST -1 | ret = %d\n",  get_entries_from_filename(ledger, NULL));

  for(test = 0; test < ntests; ++test){
    new_ledger(&ledger);

    printf("\n--------\nTEST %d", test);
    printf("\nret = %d\n", get_ledger(&ledger, strs[test], NULL, NULL));
    
    printf("\nENTRIES %d\n\n", test); 
 
    for(j = 0; j < ledger->nrows; ++j){   
      for(i = 0; i < NFIELDS - 1; ++i)
        printf("%s\t", ledger->entries[i][j]);
      printf("%s", ledger->entries[NFIELDS - 1][j]); 
      printf("\n");     
    }
    
    printf("\nTOTALS %d\n\n", test);
    
    printf("\ncredits: \n");
    for(i = 0; i < ledger->ncredits; ++i){
      printf("\n_%s\n", ledger->credits[i]);
      printf("  NOTTHEREYET:\t%0.2f\n", ledger->credit_totals[i][I_NOT_THERE_YET]);
      printf("  PENDING:\t%0.2f\n", ledger->credit_totals[i][I_PENDING]);
      printf("  CLEARED:\t%0.2f\n", ledger->credit_totals[i][I_CLEARED]);
      printf("  PENDING BAL:\t%0.2f\n", ledger->credit_totals[i][I_PENDING_BAL]);
      printf("  OVERALL BAL:\t%0.2f\n", ledger->credit_totals[i][I_OVERALL_BAL]);
    }
     printf("\n\n");  
    
    printf("banks:\n\n");    
    for(i = 0; i < ledger->nbanks; ++i){
      printf("\n_%s | ", ledger->banks[i]);
      
            printf("  NOTTHEREYET:\t%0.2f\n", ledger->bank_totals[i][I_NOT_THERE_YET]);
      printf("  PENDING:\t%0.2f\n", ledger->bank_totals[i][I_PENDING]);
      printf("  CLEARED:\t%0.2f\n", ledger->bank_totals[i][I_CLEARED]);
      printf("  PENDING BAL:\t%0.2f\n", ledger->bank_totals[i][I_PENDING_BAL]);
      printf("  OVERALL BAL:\t%0.2f\n", ledger->bank_totals[i][I_OVERALL_BAL]);
      
      for(j = 0; j < ledger->npartitions[i]; ++j)
        printf("_%s(%0.2f) ", ledger->partitions[i][j], ledger->partition_totals[i][j]);    
             printf("\n");     
    }
     printf("\n\n");   
      
    free_ledger(ledger);
  }  

  for(test = 0; test < ntests; ++test)
    free(strs[test]);
  free(strs);








/*

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
  strcpy(strs[10], L10);
  
  
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("  FROM STREAMS \n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");

  printf("\n--------\nTEST -1 | ret = %d\n",  get_entries_from_filename(ledger, NULL));

  for(test = 0; test < ntests; ++test){
    new_ledger(&ledger);

    printf("\n--------\nTEST %d", test);
    
    fp = fopen(strs[test], "r");
    printf("\nret = %d\n", get_ledger(&ledger, NULL, fp, NULL));
    if(fp != NULL)
      fclose(fp);
    
    printf("\nENTRIES %d\n\n", test); 
 
    for(j = 0; j < ledger->nrows; ++j){   
      for(i = 0; i < NFIELDS - 1; ++i)
        printf("%s\t", ledger->entries[i][j]);
      printf("%s", ledger->entries[NFIELDS - 1][j]); 
      printf("\n");     
    }
    
    printf("\nTOTALS %d\n\n", test);
    
    printf("\ncredits: \n");
    for(i = 0; i < ledger->ncredits; ++i){
      printf("\n_%s\n", ledger->credits[i]);
      printf("  NOTTHEREYET:\t%0.2f\n", ledger->credit_totals[i][I_NOT_THERE_YET]);
      printf("  PENDING:\t%0.2f\n", ledger->credit_totals[i][I_PENDING]);
      printf("  CLEARED:\t%0.2f\n", ledger->credit_totals[i][I_CLEARED]);
      printf("  PENDING BAL:\t%0.2f\n", ledger->credit_totals[i][I_PENDING_BAL]);
      printf("  OVERALL BAL:\t%0.2f\n", ledger->credit_totals[i][I_OVERALL_BAL]);
    }
     printf("\n\n");  
    
    printf("banks:\n\n");    
    for(i = 0; i < ledger->nbanks; ++i){
      printf("\n_%s | ", ledger->banks[i]);
      
            printf("  NOTTHEREYET:\t%0.2f\n", ledger->bank_totals[i][I_NOT_THERE_YET]);
      printf("  PENDING:\t%0.2f\n", ledger->bank_totals[i][I_PENDING]);
      printf("  CLEARED:\t%0.2f\n", ledger->bank_totals[i][I_CLEARED]);
      printf("  PENDING BAL:\t%0.2f\n", ledger->bank_totals[i][I_PENDING_BAL]);
      printf("  OVERALL BAL:\t%0.2f\n", ledger->bank_totals[i][I_OVERALL_BAL]);
      
      for(j = 0; j < ledger->npartitions[i]; ++j)
        printf("_%s(%0.2f) ", ledger->partitions[i][j], ledger->partition_totals[i][j]);    
             printf("\n");     
    }
     printf("\n\n");   
      
    free_ledger(ledger);
  }  

  for(test = 0; test < ntests; ++test)
    free(strs[test]);
  free(strs);









  strs = malloc(ntests * sizeof(char*));
  for(i = 0; i < ntests; ++i)
    strs[i] = calloc(2000, sizeof(char));

  strcpy(strs[0], S0);
  strcpy(strs[1], S1);
  strcpy(strs[2], S2);
  strcpy(strs[3], S3);
  strcpy(strs[4], S4);
  strcpy(strs[5], S5);
  strcpy(strs[6], S6);
  strcpy(strs[7], S7);
  strcpy(strs[8], S8);
  strcpy(strs[9], S9);
  strcpy(strs[10], S10);
  
  
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("  FROM STRINGS \n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");
  printf("------------------------------------\n");

  printf("\n--------\nTEST -1 | ret = %d\n",  get_entries_from_filename(ledger, NULL));

  for(test = 0; test < ntests; ++test){
    new_ledger(&ledger);

    printf("\n--------\nTEST %d", test);
    

    printf("\nret = %d\n", get_ledger(&ledger, NULL, NULL, strs[test]));
    
    printf("\nENTRIES %d\n\n", test); 
 
    for(j = 0; j < ledger->nrows; ++j){   
      for(i = 0; i < NFIELDS - 1; ++i)
        printf("%s\t", ledger->entries[i][j]);
      printf("%s", ledger->entries[NFIELDS - 1][j]); 
      printf("\n");     
    }
    
    printf("\nTOTALS %d\n\n", test);
    
    printf("\ncredits: \n");
    for(i = 0; i < ledger->ncredits; ++i){
      printf("\n_%s\n", ledger->credits[i]);
      printf("  NOTTHEREYET:\t%0.2f\n", ledger->credit_totals[i][I_NOT_THERE_YET]);
      printf("  PENDING:\t%0.2f\n", ledger->credit_totals[i][I_PENDING]);
      printf("  CLEARED:\t%0.2f\n", ledger->credit_totals[i][I_CLEARED]);
      printf("  PENDING BAL:\t%0.2f\n", ledger->credit_totals[i][I_PENDING_BAL]);
      printf("  OVERALL BAL:\t%0.2f\n", ledger->credit_totals[i][I_OVERALL_BAL]);
    }
     printf("\n\n");  
    
    printf("banks:\n\n");    
    for(i = 0; i < ledger->nbanks; ++i){
      printf("\n_%s | ", ledger->banks[i]);
      
            printf("  NOTTHEREYET:\t%0.2f\n", ledger->bank_totals[i][I_NOT_THERE_YET]);
      printf("  PENDING:\t%0.2f\n", ledger->bank_totals[i][I_PENDING]);
      printf("  CLEARED:\t%0.2f\n", ledger->bank_totals[i][I_CLEARED]);
      printf("  PENDING BAL:\t%0.2f\n", ledger->bank_totals[i][I_PENDING_BAL]);
      printf("  OVERALL BAL:\t%0.2f\n", ledger->bank_totals[i][I_OVERALL_BAL]);
      
      for(j = 0; j < ledger->npartitions[i]; ++j)
        printf("_%s(%0.2f) ", ledger->partitions[i][j], ledger->partition_totals[i][j]);    
             printf("\n");     
    }
     printf("\n\n");   
      
    free_ledger(ledger);
  }  

  for(test = 0; test < ntests; ++test)
    free(strs[test]);
  free(strs);

*/




  return 0;
}
