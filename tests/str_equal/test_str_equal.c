#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char **a, **b, **c, **d, **e, **f, **g;
  a = malloc(sizeof(char*));
  b = malloc(sizeof(char*)); 
  c = malloc(sizeof(char*));
  d = malloc(sizeof(char*));
  e = malloc(sizeof(char*));
  f = malloc(sizeof(char*));
  g = malloc(sizeof(char*));

  *a = malloc(100 * sizeof(char));
  *b = malloc(100 * sizeof(char));
  *c = malloc(100 * sizeof(char));   
  *d = malloc(100 * sizeof(char));
  *e = malloc(100 * sizeof(char));   
  *f = malloc(100 * sizeof(char));
  
  strcpy(*a, "gd");
  strcpy(*b, "bad");
  strcpy(*c, "gda");
  strcpy(*d, "\0");
  strcpy(*e, "\0lk;sd");
  strcpy(*f, "");
  *g = NULL;
   
  printf("a=%s\ta=%s\t%d\n", *a, *a, str_equal(* a, *a));
  printf("a=%s\tb=%s\t%d\n", *a, *b, str_equal(* a, *b));
  printf("a=%s\tc=%s\t%d\n", *a, *c, str_equal(* a, *c));
  printf("a=%s\td=%s\t%d\n", *a, *d, str_equal(* a, *d));
  printf("a=%s\te=%s\t%d\n", *a, *e, str_equal(* a, *e));
  printf("a=%s\tf=%s\t%d\n", *a, *f, str_equal(* a, *f));
  printf("a=%s\tg=%s\t%d\n\n", *a, *g, str_equal(* a, *g));
  
  printf("b=%s\tb=%s\t%d\n", *b, *b, str_equal(* b, *b));
  printf("b=%s\tc=%s\t%d\n", *b, *c, str_equal(* b, *c));
  printf("b=%s\td=%s\t%d\n", *b, *d, str_equal(* b, *d));
  printf("b=%s\te=%s\t%d\n", *b, *e, str_equal(* b, *e));
  printf("b=%s\tf=%s\t%d\n", *b, *f, str_equal(* b, *f));
  printf("b=%s\tg=%s\t%d\n\n", *b, *g, str_equal(* b, *g));

  printf("c=%s\tc=%s\t%d\n", *c, *c, str_equal(* c, *c));
  printf("c=%s\td=%s\t%d\n", *c, *d, str_equal(* c, *d));
  printf("c=%s\te=%s\t%d\n", *c, *e, str_equal(* c, *e));
  printf("c=%s\tf=%s\t%d\n", *c, *f, str_equal(* c, *f));
  printf("c=%s\tg=%s\t%d\n\n", *c, *g, str_equal(* c, *g));

  printf("d=%s\td=%s\t%d\n", *d, *d, str_equal(* d, *d));
  printf("d=%s\te=%s\t%d\n", *d, *e, str_equal(* d, *e));
  printf("d=%s\tf=%s\t%d\n", *d, *f, str_equal(* d, *f));
  printf("d=%s\tg=%s\t%d\n\n", *d, *g, str_equal(* d, *g));

  printf("e=%s\te=%s\t%d\n", *e, *e, str_equal(* e, *e));
  printf("e=%s\tf=%s\t%d\n", *e, *f, str_equal(* e, *f));
  printf("e=%s\tg=%s\t%d\n\n", *e, *g, str_equal(* e, *g));
  
  printf("f=%s\tf=%s\t%d\n", *f, *f, str_equal(* f, *f));
  printf("f=%s\tg=%s\t%d\n\n", *f, *g, str_equal(* f, *g));

  printf("g=%s\tg=%s\t%d\n\n", *g, *g, str_equal(* g, *g));
  
  free(*a);
  free(*b);
  free(*c);
  free(*d);
  free(*e);
  free(*f);
  
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  free(f);
  free(g);
  
  return 0;
}
