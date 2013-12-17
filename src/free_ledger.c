/***
 *** @file free_ledger.c
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

err_t free_ledger(Ledger **ledger){

  err_t ret = LSUCCESS;

  if(ledger == NULL)
    return LFAILURE;
    
  if(*ledger == NULL)
    return LFAILURE;

  if((*ledger)->filename != NULL){
    free((*ledger)->filename);
    (*ledger)->filename = NULL;
  }
  
  if(free_entries(*ledger) == LFAILURE)
    ret = LFAILURE; 

  free(*ledger);
  *ledger = NULL;
  
  return ret;
}
