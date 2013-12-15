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
 
 /************************************************************************* 
 *** COLUMN INDICES IN LEDGER FILE. ***************************************
 *** THESE NUMBERS DEFINE THE ORDERING OF THE COLUMNS *********************
 *** MUST INCLUDE ALL THE NUMBERS FROM 0 TO 5 INCLUSIVE. ******************
 **************************************************************************/

#define AMOUNT        0   /*** COLUMN FOR TRANSACTION AMOUNTS *************/
#define STATUS        1   /*** COLUMN FOR TRANSACTION STATUS CODES ********/
#define CREDIT        2   /*** COLUMN FOR NAMES OF CREDIT ACCOUNTS ********/
#define BANK          3   /*** COLUMN FOR NAMES OF BANK ACCOUNTS **********/       
#define PARTITION     4   /*** COLUMN FOR NAMES OF BANK PARTITIONS ********/
#define DESCRIPTION   5   /*** COLUMN FOR DESCRIPTIONS OF TRANSACTIONS ****/


/************************************************************************** 
 *** USER-DEFINED ROW AND COLUMN SEPARATORS *******************************
 *** EACH CHARACTER IN EACH OF THE STRINGS BELOW IS A SEPARATOR ***********
 *** STRINGS OF SEPARATORS MUST BE NO LONGER THAN NUM_SEPARATORS **********
 **************************************************************************/

#define ROW_SEPARATORS      "\n\r"
#define COLUMN_SEPARATORS   "\t"

/************************************************************************** 
 *** USER-DEFINED TRANSACTION STATUSES CODES ******************************
 **************************************************************************/

#define CREDIT_NOT_THERE_YET   "cn"   /*** HASN'T REACHED CREDIT COMPANY YET ********/
#define CREDIT_PENDING         "cp"   /*** PENDING CHARGE IN CREDIT ACCOUNT *********/
#define CREDIT_CHARGED         "c"    /*** CLEARED IN CREDIT ACCOUNT BUT NOT PAID ***/
#define NOT_THERE_YET          "n"    /*** HASN'T REACHED BANK YET ******************/
#define PENDING                "p"    /*** PENDING IN BANK **************************/
#define LOCKED                 "l"    /*** CLEARED, BUT NOT OKAY TO CONDENSE ********/


/************************************************************************** 
 *** USER-DEFINED OPTIONS FOR OUTPUT SUMMARIES ****************************
 **************************************************************************/

#define PRINT_EMPTY_ACCOUNTS 0  /*** SET TO 1 TO INCLUDE EMPTY ACCOUNTS IN SUMMARY ****
                                 *** SET TO 0 TO IGNORE ACCOUNTS WITH $0.00 BALANCE ***/

#define USE_COLOR   1  /*** SET TO 1 TO ENABLE COLOR-CODED PRINTING TO THE TERMINAL ***/  	/* NEED TO IMPLEMENT */
                       /*** SET TO 0 FOR NO COLORING **********************************/

#define NORMAL_COLOR     "\x1B[0m"    /*** REGULAR TEXT ******/
#define NEGATIVE_COLOR   "\x1B[31m"   /*** NEGATIVE TOTALS ***/
#define POSITIVE_COLOR   "\x1B[32m"   /*** POSITIVE TOTALS ***/
#define ZERO_COLOR       "\x1B[34m"   /*** EMPTY TOTALS ******/

#endif
