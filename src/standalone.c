/**
 * @file standalone.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Top level function of the standalone command line
 *          interface version of this program. Receives 
 *          arguments argc and argv directly from int main.
 *          If the user calls the program with no arguments,
 *          standalone will print the usage information and
 *          return. If the user gives one argument, standalone
 *          will take the argument as the full path of a ledger
 *          file, read it in, and print it in color to the 
 *          Terminal window. If two arguments are given,
 *          standalone will read a ledger from the file whose
 *          full path is given by the first argument, condense
 *          the ledger, and then write the condensed ledger
 *          to a new file whose full path is the second
 *          argument.
 */
err_t standalone(int argc, char **argv){
  Ledger *ledger = NULL;

  /* If there is 1 argument, print a summary of the ledger to the Terminal window */

  if(argc == 2){

    if(get_ledger(&ledger, argv[1], NULL, NULL) == LFAILURE){
      print_summary_to_stream(ledger, stdout, USE_COLOR);
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(print_summary_to_stream(ledger, stdout, USE_COLOR) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(free_ledger(&ledger) == LFAILURE)
      return LFAILURE;

  /* If there are 2 arguments, condense ledger and save to file */

  } else if(argc == 3){ 

    if(get_ledger(&ledger, argv[1], NULL, NULL) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(clean(ledger, LNO) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(print_ledger_to_filename(ledger, argv[2]) == LFAILURE){
      free_ledger(&ledger);
      return LFAILURE;
    }

    if(free_ledger(&ledger) == LFAILURE)
      return LFAILURE;

  /* If no input or output files are given, print usage information and return */

  } else{
    if(usage() == LFAILURE)
      return LFAILURE; 
  }

  return LSUCCESS;
}
