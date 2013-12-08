#ifndef USER_SETTINGS_H
#define USER_SETTINGS_H

/***
 *** @file ledger.h
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://will-landau.com
 *** @date December 1, 2013
 *** @license GPL 3.0
 *** @about User settings for Dynamic Ledger
 ***/
 
 /*************************************************************************************** 
 *** USER-DEFINED COLUMN ASSIGNMENTS IN LEDGER FILE. ***********************************
 *** MUST INCLUDE ALL THE NUMBERS FROM 0 TO 5 INCLUSIVE. *******************************
 ***************************************************************************************/

#define AMOUNT        0   /*** COLUMN FOR TRANSACTION AMOUNTS ************/
#define STATUS        1   /*** COLUMN FOR TRANSACTION STATUS CODES *******/
#define CREDIT        2   /*** COLUMN FOR NAMES OF CREDIT ACCOUNTS *******/
#define BANK          3   /*** COLUMN FOR NAMES OF BANK ACCOUNTS *********/       
#define PARTITION     4   /*** COLUMN FOR NAMES OF BANK PARTITIONS *******/
#define DESCRIPTION   5   /*** COLUMN FOR DESCRIPTIONS OF TRANSACTIONS ***/


/*************************************************************************************** 
 *** USER-DEFINED ROW AND COLUMN SEPARATORS ********************************************
 *** EACH CHARACTER IN EACH OF THE STRINGS BELOW IS A SEPARATOR ************************
 *** STRINGS OF SEPARATORS MUST BE NO LONGER THAN NUM_SEPARATORS ***********************
 ***************************************************************************************/

#define ROW_SEPARATORS      "\n\r"													/* NEED TO IMPLEMENT */
#define COLUMN_SEPARATORS   "\t"          										/* NEED TO IMPLEMENT */
#define NUM_SEPARATORS      16												/* NEED TO IMPLEMENT */

/*************************************************************************************** 
 *** USER-DEFINED TRANSACTION STATUSES CODES *******************************************
 ***************************************************************************************/

#define CREDIT_NOT_THERE_YET   "cn"   /*** HASN'T REACHED CREDIT COMPANY YET ***/
#define CREDIT_PENDING         "cp"   /*** PENDING CHARGE IN CREDIT ACCOUNT ****/
#define CREDIT_CLEARED         "c"    /*** CLEARED IN CREDIT ACCOUNT ***********/
#define NOT_THERE_YET          "n"    /*** HASN'T REACHED BANK YET *************/
#define PENDING                "p"    /*** PENDING IN BANK *********************/
#define LOCKED                 "l"    /*** CLEARED, BUT NOT OKAY TO CONDENSE ***/


/*************************************************************************************** 
 *** USER-DEFINED OPTIONS FOR COLORS IN OUTPUT SUMMARIES *******************************
 ***************************************************************************************/

#define USE_COLOR   1  /*** SET TO 1 TO ENABLE COLOR-CODED PRINTING TO THE TERMINAL ***/  	/* NEED TO IMPLEMENT */
                       /*** SET TO 0 FOR NO COLORING **********************************/

#define NORMAL_COLOR     "\x1B[0m"    /*** REGULAR TEXT ******/
#define NEGATIVE_COLOR   "\x1B[31m"   /*** NEGATIVE TOTALS ***/
#define POSITIVE_COLOR   "\x1B[32m"   /*** POSITIVE TOTALS ***/
#define ZERO_COLOR       "\x1B[34m"   /*** EMPTY TOTALS ******/
 
 #endif