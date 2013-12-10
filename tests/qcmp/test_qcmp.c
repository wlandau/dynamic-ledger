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
   
  printf("%s\t%s\t%d\n", *a, *a, qcmp((void *) a, (void *)a));
  printf("%s\t%s\t%d\n", *a, *b, qcmp((void *) a, (void *)b));
  printf("%s\t%s\t%d\n", *a, *c, qcmp((void *) a, (void *)c));
  printf("%s\t%s\t%d\n", *a, *d, qcmp((void *) a, (void *)d));
  printf("%s\t%s\t%d\n\n", *a, *e, qcmp((void *) a, (void *)e));
  
  printf("%s\t%s\t%d\n", *b, *b, qcmp((void *) b, (void *)b));
  printf("%s\t%s\t%d\n", *b, *c, qcmp((void *) b, (void *)c));
  printf("%s\t%s\t%d\n", *b, *d, qcmp((void *) b, (void *)d));
  printf("%s\t%s\t%d\n\n", *b, *e, qcmp((void *) b, (void *)e));

  printf("%s\t%s\t%d\n", *c, *c, qcmp((void *) c, (void *)c));
  printf("%s\t%s\t%d\n", *c, *d, qcmp((void *) c, (void *)d));
  printf("%s\t%s\t%d\n\n", *c, *e, qcmp((void *) c, (void *)e));

  printf("%s\t%s\t%d\n", *d, *d, qcmp((void *) d, (void *)d));
  printf("%s\t%s\t%d\n\n", *d, *e, qcmp((void *) d, (void *)e));

  printf("%s\t%s\t%d\n\n", *e, *e, qcmp((void *) e, (void *)e));
  
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
