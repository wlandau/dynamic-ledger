#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NIL "\0"
#define FIELDSIZE 128

void print_array(char **a, int n){
  int i;
  for(i = 0; i < n; ++i)
    printf("%s ", a[i]);
  printf(" | n = %d\n", n);
}

void insert_in_array(char ***a, int at, int *n){
  int i;
  char **tmp, **b;

  if(a == NULL)
    return;
  
  if(at < 0 || at >= *n){
    fprintf(stderr, "Error: bad row index.\n");
    return;
  }
 
  b = malloc((*n + 1) * sizeof(char*));
 
  for(i = 0; i < (*n + 1); ++i)
    b[i] = malloc(FIELDSIZE * sizeof(char));
    
  for(i = 0; i < at; ++i)
    strcpy(b[i], (*a)[i]);
  
  strcpy(b[i], NIL); 
  
  printf("--%lu-%lu-\n", strlen("\0"), strlen(""));
  
  for(i = at + 1; i < *n + 1; ++i)
    strcpy(b[i], (*a)[i - 1]);

   
  tmp = *a;
  *a = b;
  
  for(i = 0; i < *n; ++i)
    free(tmp[i]);
  free(tmp);
  ++(*n); 
}

void remove_from_array(char **a, int at, int *n){
  int i;
  
  if(a == NULL)
    return;
  
  if(at < 0 || at >= *n){
    fprintf(stderr, "Error: bad row index.\n");
    return;
  }
  
  for(i = at; i < (*n - 1); ++i)
    strcpy(a[i], a[i + 1]);
  
  free(a[*n - 1]);
  --(*n); 
}

char **makeA(){
  int i, n = 10;
  char s[10];
  char **a = malloc(n * sizeof(char*));
  
  for(i = 0; i < n; ++i){
    a[i] = malloc(FIELDSIZE * sizeof(char));
    sprintf(s, "%d%d", i, i);
    strcpy(a[i], s);
  }
  
  return a;
}

void freeA(char **a, int n){
  int i;
  
  if(a == NULL)
    return;

  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);
}

int main(){
  int i, n = 10;
  char **a;
  
  for(i = -1; i < n + 1; ++i){
    n = 10;
    a = makeA();
    printf("%d | ", i);
    print_array(a, n);
    remove_from_array(a, i, &n);
    printf("%d | ", i);
    print_array(a, n);
    freeA(a, n);
    printf("\n");
  }
  
  printf("\n\n");
  
  n = 10;
  for(i = -1; i < n + 1; ++i){
    n = 10;
    a = makeA();
    printf("%d | ", i);
    print_array(a, n);
    insert_in_array(&a, i, &n);
    printf("%d | ", i);
    print_array(a, n);
    freeA(a, n);
    printf("\n");
  }
  
  return 0;
}
