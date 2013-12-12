#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  int i, n = 10, nunique, ret;
  char **a = malloc(n * sizeof(char*)), **s;
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
    
  printf("\n");  
  strcpy(a[0], "a");  
  strcpy(a[1], "");  
  strcpy(a[2], "");  
  strcpy(a[3], "\0");  
  strcpy(a[4], "ab");  
  strcpy(a[5], "b");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], " ");    
  strcpy(a[9], "good");     
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);
        
  printf("nunique = %d\n\n", nunique);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");              
        
  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);

  for(i = 0; i < nunique; ++i)
    free(s[i]);
  free(s);
  nunique = 0;
  
  
  
  printf("\n\n TEST 1A!!!\n\n");
  
  
  n = 10;
  a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i){
    if(i != 1)
      a[i] = malloc(100 * sizeof(char));
    else
      a[i] = NULL;
  }
    
  printf("\n");  
  strcpy(a[0], "a");   
  strcpy(a[2], "");  
  strcpy(a[3], "\0");  
  strcpy(a[4], "ab");  
  strcpy(a[5], "b");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], " ");    
  strcpy(a[9], "good");     
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);
          
  printf("nunique = %d\n\n", nunique);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");              
        
  for(i = 0; i < n; ++i)
    if(a[i] != NULL)
      free(a[i]);
  free(a);

  for(i = 0; i < nunique; ++i)
    free(s[i]);
  free(s);
  nunique = 0;

  
  
  

printf("\n\n TEST 2!!!\n\n");

n = 10;
a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
    
  printf("\n");  
  strcpy(a[0], "good");  
  strcpy(a[1], "n");  
  strcpy(a[2], "n");  
  strcpy(a[3], "n");  
  strcpy(a[4], "gooda");  
  strcpy(a[5], "badd");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], "n");    
  strcpy(a[9], "good");     
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);
        
  printf("nunique = %d\n\n", nunique);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");              
        
  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);

  for(i = 0; i < nunique; ++i)
    free(s[i]);
  free(s);
  nunique = 0;


printf("\n\n TEST 2A!!!\n\n");

n = 10;
a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
    
  printf("\n");  
  strcpy(a[0], "\0");  
  strcpy(a[1], "n");  
  strcpy(a[2], "n");  
  strcpy(a[3], "n");  
  strcpy(a[4], "gooda");  
  strcpy(a[5], "badd");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], "n");    
  strcpy(a[9], "good");     
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);
        
  printf("nunique = %d\n\n", nunique);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");              
        
  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);

  for(i = 0; i < nunique; ++i)
    free(s[i]);
  free(s);
  nunique = 0;
  
  
printf("\n\n TEST 2B!!!\n\n");

n = 10;
a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
    
  printf("\n");  
  strcpy(a[0], "\0");  
  strcpy(a[1], "n");  
  strcpy(a[2], "n");  
  strcpy(a[3], "n");  
  strcpy(a[4], "gooda");  
  strcpy(a[5], "badd");  
  strcpy(a[6], "\0");  
  strcpy(a[7], "\0alks;dj");    
  strcpy(a[8], "n");    
  strcpy(a[9], "good");     
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);
        
  printf("nunique = %d\n\n", nunique);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");              
        
  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);

  for(i = 0; i < nunique; ++i)
    free(s[i]);
  free(s);
  nunique = 0;






printf("\n\n TEST 3!!!\n\n");


  a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
    
  printf("\n");  
  strcpy(a[0], "good");  
  strcpy(a[1], "");  
  strcpy(a[2], "");  
  strcpy(a[3], "\0");  
  strcpy(a[4], "gooda");  
  strcpy(a[5], "badd");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], " ");    
  strcpy(a[9], "good");     
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  n = 0;
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);

  printf("nunique = %d\n\n", nunique);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");              
        
  for(i = 0; i < 10; ++i)
    if(a[i] != NULL)
      free(a[i]);
  if(a != NULL)
    free(a);


printf("\n\nTEST 4!!! \n\n");

  a = NULL;
  n = 5;
  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);

printf("\n\nTEST 5!!! \n\n");


  n = 1;
  a = malloc(n * sizeof(char*));
  *a = NULL;

  printf("*a = %s\n", *a);

  ret = unique(a, n, &s, &nunique);
    printf("\n---\nRETURN VALUE OF UNIQUE() IS %d\n---\n", ret);
        
  printf("nunique = %d\n\n", nunique);
  
  printf("*a = %s\n", *a);
  
  for(i = 0; i < nunique; ++i)
    printf("s[%d] = %s\n",i, s[i]);
  printf("\n");        
        
  for(i = 0; i < 1; ++i)
    if(a[i] != NULL)
      free(a[i]);
  if(a != NULL)
    free(a);
  
  for(i = 0; i < nunique; ++i)
    if(s[i] != NULL)
      free(s[i]);
  if(s != NULL)
    free(s);

  return 0;
}
