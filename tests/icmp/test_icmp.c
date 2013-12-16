#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  int *a, *b, *c, *d, *e;
  a = malloc(sizeof(int));
  b = malloc(sizeof(int)); 
  c = malloc(sizeof(int));
  d = malloc(sizeof(int));
  e = malloc(sizeof(int));

  *a = 1;
  *b = 2;
  *c = 3; 
  *d = 4;
  *e = 5;

  printf("%d\t%d\t%d\n", *a, *a, icmp((void *) a, (void *)a));
  printf("%d\t%d\t%d\n", *a, *b, icmp((void *) a, (void *)b));
  printf("%d\t%d\t%d\n", *a, *c, icmp((void *) a, (void *)c));
  printf("%d\t%d\t%d\n", *a, *d, icmp((void *) a, (void *)d));
  printf("%d\t%d\t%d\n\n", *a, *e, icmp((void *) a, (void *)e));

  printf("%d\t%d\t%d\n", *b, *a, icmp((void *) b, (void *)a));  
  printf("%d\t%d\t%d\n", *b, *b, icmp((void *) b, (void *)b));
  printf("%d\t%d\t%d\n", *b, *c, icmp((void *) b, (void *)c));
  printf("%d\t%d\t%d\n", *b, *d, icmp((void *) b, (void *)d));
  printf("%d\t%d\t%d\n\n", *b, *e, icmp((void *) b, (void *)e));

  printf("%d\t%d\t%d\n", *c, *a, icmp((void *) c, (void *)a));
  printf("%d\t%d\t%d\n", *c, *b, icmp((void *) c, (void *)b));
  printf("%d\t%d\t%d\n", *c, *c, icmp((void *) c, (void *)c));
  printf("%d\t%d\t%d\n", *c, *d, icmp((void *) c, (void *)d));
  printf("%d\t%d\t%d\n\n", *c, *e, icmp((void *) c, (void *)e));

  printf("%d\t%d\t%d\n", *d, *a, icmp((void *) d, (void *)a));
  printf("%d\t%d\t%d\n", *d, *b, icmp((void *) d, (void *)b));
  printf("%d\t%d\t%d\n", *d, *c, icmp((void *) d, (void *)c));
  printf("%d\t%d\t%d\n", *d, *d, icmp((void *) d, (void *)d));
  printf("%d\t%d\t%d\n\n", *d, *e, icmp((void *) d, (void *)e));

  printf("%d\t%d\t%d\n", *e, *a, icmp((void *) e, (void *)a));
  printf("%d\t%d\t%d\n", *e, *b, icmp((void *) e, (void *)b));
  printf("%d\t%d\t%d\n", *e, *c, icmp((void *) e, (void *)c));
  printf("%d\t%d\t%d\n", *e, *d, icmp((void *) e, (void *)d));
  printf("%d\t%d\t%d\n\n", *e, *e, icmp((void *) e, (void *)e));

  
  free(a);
  free(b);
  free(c);
  free(d);
  free(e);
  return 0;
}
