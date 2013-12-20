/**
 * @file str_strip.c
 * @author Will Landau (http://www.will-landau.com/)
 */

#include <errno.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

/** 
 * @details Strips leading and trailing whitespace from a character string.
 */
err_t str_strip(char *s){ /* taken from a stackoverflow forum */
  char *start;
  char *end;

  /* Exit if param is NULL pointer */
  if (s == NULL)
    return LFAILURE;

  /* Skip over leading whitespace */
  start = s;
  while ((*start) && space(*start))
    start++;      

  /* Is string just whitespace? */
  if (!(*start)){         
    *s = 0x00; /* Truncate entire string */
    return LSUCCESS;     
  }     

  /* Find end of string */
  end = start;
  while (*end)         
    end++;

  /* Step back from NULL */
  end--;      

  /* Step backward until first non-whitespace */
  while ((end != start) && space(*end))         
    end--;     

  /* Chop off trailing whitespace */
  *(end + 1) = 0x00;

  /* If had leading whitespace, then move entire string back to beginning */
  if (s != start)
    memmove(s, start, end-start+2);      

  return LSUCCESS; 
} 
