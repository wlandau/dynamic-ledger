/**
 * @file usage.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Prints usage details of the command line interface version
 *          of the program.
 */
err_t usage(){
  printf("\nUsage: to summarize the ledger,\n$ ./ledger [LEDGER_FILE]\n");
  printf("\nTo condense the ledger,\n$ ");
  printf("./ledger [INTPUT_LEDGER_FILE] [OUTTPUT_LEDGER_FILE]\n");
  printf("\nSee the tutorial for details.\n");
  
  return LSUCCESS;
}
