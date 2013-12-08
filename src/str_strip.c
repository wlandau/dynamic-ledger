/***
 *** @file str_strip.c
 *** @author Will Landau
 *** @email will.landau@gmail.com
 ***/

#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

void str_strip(char *s){ /* taken from a stackoverflow forum */
  char *start;
  char *end;

  /* Exit if param is NULL pointer */
  if (s == NULL)
    return;

  /* Skip over leading whitespace */
  start = s;
  while ((*start) && is_space(*start))
    start++;      

  /* Is string just whitespace? */
  if (!(*start)){         
    *s = 0x00; /* Truncate entire string */
    return;     
  }     

  /* Find end of string */
  end = start;
  while (*end)         
    end++;

  /* Step back from NULL */
  end--;      

  /* Step backward until first non-whitespace */
  while ((end != start) && is_space(*end))         
    end--;     

  /* Chop off trailing whitespace */
  *(end + 1) = 0x00;

  /* If had leading whitespace, then move entire string back to beginning */
  if (s != start)
    memmove(s, start, end-start+2);      

  return; 
} 
