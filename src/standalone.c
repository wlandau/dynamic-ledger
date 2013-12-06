/***
 *** @file standalone.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger-txt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int standalone(int argc, char **argv){
  if(argc == 2){
    if(summarize_file_to_stream(argv[1], stdout)){
      printf("Exiting.\n");
      return 1;
    }
  } else if(argc == 3){
    if(condense_and_print(argv[1], argv[2])){
      printf("No output produced.\nExiting.\n");
      return 1;
    }
  } else{
    usage(); 
  }

  return 0;
}

int main(int argc, char **argv){ 
  return standalone(argc, argv) ? EXIT_FAILURE : EXIT_SUCCESS;
}
