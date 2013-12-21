/**
 * @file        output_file.c
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
 * @details Checks if the output file with the given full path name
 *          is usable. That is, it tries to open the file for writing
 *          and returns LYES on success and LNO on failure.
 */
bool_t output_file(char *filename){
  FILE *fp;

  if(filename == NULL){
    fprintf(stderr, "Error: filename is null.\n");
    return LNO;
  }

  fp = fopen(filename, "w");
  if(fp == NULL){
    fprintf(stderr, 
            "Error: cannot create file, %s.\nCheck your permissions.\n", filename);
    return LNO;
  }
  fclose(fp);
  return LYES;
}
