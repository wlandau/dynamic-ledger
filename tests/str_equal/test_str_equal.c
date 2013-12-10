#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char **a, **b, **c, **d, **e;
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

  strcpy(*a, "good");
  strcpy(*b, "badd");
  strcpy(*c, "gooda");
  strcpy(*d, "\0");
  strcpy(*e, "");
   
  printf("%s\t%s\t%d\n", *a, *a, str_equal(* a, *a));
  printf("%s\t%s\t%d\n", *a, *b, str_equal(* a, *b));
  printf("%s\t%s\t%d\n", *a, *c, str_equal(* a, *c));
  printf("%s\t%s\t%d\n", *a, *d, str_equal(* a, *d));
  printf("%s\t%s\t%d\n\n", *a, *e, str_equal(* a, *e));
  
  printf("%s\t%s\t%d\n", *b, *b, str_equal(* b, *b));
  printf("%s\t%s\t%d\n", *b, *c, str_equal(* b, *c));
  printf("%s\t%s\t%d\n", *b, *d, str_equal(* b, *d));
  printf("%s\t%s\t%d\n\n", *b, *e, str_equal(* b, *e));

  printf("%s\t%s\t%d\n", *c, *c, str_equal(* c, *c));
  printf("%s\t%s\t%d\n", *c, *d, str_equal(* c, *d));
  printf("%s\t%s\t%d\n\n", *c, *e, str_equal(* c, *e));

  printf("%s\t%s\t%d\n", *d, *d, str_equal(* d, *d));
  printf("%s\t%s\t%d\n\n", *d, *e, str_equal(* d, *e));

  printf("%s\t%s\t%d\n\n", *e, *e, str_equal(* e, *e));
  
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
  return 0;
}
