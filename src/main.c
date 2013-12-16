/***
 *** @file main.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://www.will-landau.com/
 ***/

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(int argc, char **argv){
  return (standalone(argc, argv) == LSUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}
