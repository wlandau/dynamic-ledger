/**
 * @file qcmp.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/**
 * @details Comparison function for character strings in qsort.
 *          qcmp is used to sort arrays of character strings as in
 *          the function, unique.
 */
int qcmp(const void *a, const void *b){ 
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib); 
} 
