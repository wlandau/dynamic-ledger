/**
 * @file        main.c
 * @author      Will Landau (http://www.will-landau.com/)
 * @date        2013-2014
 * @copyright   GNU General Public License 3.0
 */

#include <errno.h>
#include "ledger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_settings.h"

/**
 * @details Main function of the standalone command line interface version.
 *          Just calls standalone and returns.
 */

int main(int argc, char **argv){
  return (standalone(argc, argv) == LSUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;
}
