#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char **a, **b, **c, **d, **e, *f;
  a = malloc(sizeof(char*));
  b = malloc(sizeof(char*)); 
  c = malloc(sizeof(char*));
  d = malloc(sizeof(char*));
  e = malloc(sizeof(char*));

  *a = malloc(100 * sizeof(char));
  *b = malloc(100 * sizeof(char));
  *c = malloc(100 * sizeof(char));   
  *d = malloc(100 * sizeof(char));
  *e = malloc(100 * sizeof(char));

  strcpy(*a, "g ood");
  strcpy(*b, "  badd  ");
  strcpy(*c, "\tgooda\n");
  strcpy(*d, "  ");
  strcpy(*e, "goo\n\tda");
   
  printf("|%s|\n", *a);
  printf("|%s|\n", *b);
  printf("|%s|\n", *c);
  printf("|%s|\n", *d);
  printf("|%s|\n", *e);

  str_strip(*a);
  str_strip(*b);
  str_strip(*c);
  str_strip(*d);
  str_strip(*e);

  printf("\n\nnew strings:\n\n");

  printf("|%s|\n", *a);
  printf("|%s|\n", *b);
  printf("|%s|\n", *c);
  printf("|%s|\n", *d);
  printf("|%s|\n", *e);

  free(*a);
  free(*b);
  free(*c);
  free(*d);
  free(*e);
  
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  
  f = NULL;
  printf("\n\n\nf = %s\n", f); 
  str_strip(f);
  printf("f = %s\n", f);   
  
  return 0;
}
