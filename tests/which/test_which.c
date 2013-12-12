#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  int i, n = 10;
  char **a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
    
  printf("\n");  
  strcpy(a[0], "good");  
  strcpy(a[1], "eating");  
  strcpy(a[2], "your nose");  
  strcpy(a[3], "boogie");  
  strcpy(a[4], "gooda");  
  strcpy(a[5], "badd");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], "doogie");    
  strcpy(a[9], "good");     

  qsort(a, 10, sizeof(char*), qcmp);
  
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
        
  
  for(i = 0; i < n; ++i)
    printf("%s at %d\n", a[i], which(a, a[i], n));            
  printf("\nNULL at %d\n", which(a, NULL, n));
  printf("goober at %d\n", which(a, "goober", n));
  printf("goo at %d\n\n", which(a, "goo", n));
        
  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);

printf("\n\n TEST 2!!!\n\n");

  a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i){
    a[i] = malloc(100 * sizeof(char));
  }
   
  strcpy(a[0], "good");  
  strcpy(a[1], "fun");  
  strcpy(a[2], "");  
  strcpy(a[3], "\0");  
  strcpy(a[4], "gooda");  
  strcpy(a[5], "badd");  
  strcpy(a[6], "badd");  
  strcpy(a[7], "THREE");    
  strcpy(a[8], " ");    
  strcpy(a[9], "good");     
  
  qsort(a, 10, sizeof(char*), qcmp);

  printf("\n");   
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
        
  
  for(i = 0; i < n; ++i)
    printf("%s at %d\n", a[i], which(a, a[i], n));            
  printf("\nNULL at %d\n", which(a, NULL, n));
  printf("goober at %d\n", which(a, "goober", n));
  printf("goo at %d\n\n", which(a, "goo", n));
        
  for(i = 0; i < n; ++i)
    free(a[i]);
  free(a);


printf("\n\n TEST 3!!!\n\n");


  a = malloc(n * sizeof(char*));
  for(i = 0; i < n; ++i)
    a[i] = malloc(100 * sizeof(char));
     
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

  qsort(a, 10, sizeof(char*), qcmp);

  printf("\n");   
  for(i = 0; i < n; ++i)
    printf("a[%d] = %s\n",i, a[i]);
  printf("\n");   
  
  n = 0;
  printf("\nNULL at %d\n", which(a, NULL, n));
  printf("good at %d\n", which(a, "good", n));
  printf("goober at %d\n", which(a, "goober", n));     
        
  for(i = 0; i < 10; ++i)
    if(a[i] != NULL)
      free(a[i]);
  if(a != NULL)
    free(a);

printf("\n\nTEST 4!!! \n\n");

  a = NULL;
  n = 5;
  printf("\nNULL at %d\n", which(a, NULL, n));
  printf("good at %d\n\n", which(a, "good", n)); 
  printf("goober at %d\n\n", which(a, "goober", n));      

  return 0;
}
