#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  char good[400], bad[400];
  
  printf("\n\nError status = %d for file, %s\n\n", output_file(NULL), NULL);  
  
  strcpy(good, "out.txt");
  printf("\n\nError status = %d for file, %s\n\n", output_file(good), good);

  strcpy(bad, "../main");
  printf("\n\nError status = %d for file, %s\n\n", output_file(bad), bad);

  return 0;
}
