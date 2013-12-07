#ifndef LEDGER_TXT_H
#define LEDGER_TXT_H

/***
 *** @file ledger-txt.h
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://will-landau.com
 *** @date December 1, 2013
 *** @license GPL 3.0
 *** @about Ledger.txt: minimalist personal accounting software. 
 ***        See README.txt for details. 
 ***/

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
 *** USER-DEFINED COLOR CODES FOR OUTPUT SUMMARIES *************************************
 ***************************************************************************************/

#define NORMAL_COLOR     "\x1B[0m"    /*** REGULAR TEXT ******/
#define NEGATIVE_COLOR   "\x1B[31m"   /*** NEGATIVE TOTALS ***/
#define POSITIVE_COLOR   "\x1B[32m"   /*** POSITIVE TOTALS ***/
#define ZERO_COLOR       "\x1B[34m"   /*** EMPTY TOTALS ******/


/*************************************************************************************** 
 *** INDICES FOR CREDIT AND BANK TOTALS ************************************************
 ***************************************************************************************/

#define I_NOT_THERE_YET   0
#define I_PENDING         1
#define I_CLEARED         2
#define I_OVERALL         3
#define I_PENDING_BAL     4														/* NEED TO IMPLEMENT WHEN ALLOCATING/CALCULATING TOTALS AND SUMMARIZING */
#define N_TOTALS          5														/* NEED TO IMPLEMENT WHEN ALLOCATING/CALCULATING TOTALS AND SUMMARIZING */

/*************************************************************************************** 
 *** INTERNAL PARAMETERS ***************************************************************
 ***************************************************************************************/

#define ENTRYSIZE      256
#define EPS            0.004999
#define FILENAMESIZE   256
#define LINESIZE       4096
#define NFIELDS        6
#define NIL            "\0"


/*************************************************************************************** 
 *** DATA TYPES ************************************************************************
 ***************************************************************************************/

typedef int err_t;

typedef struct {
  char *filename, **banks, **credits, ***partitions, ***entries;
  int nrows, nbanks, ncredits, *npartitions; 
  double **bank_totals, **credit_totals, **partition_totals;            
} Ledger;


/*************************************************************************************** 
 *** UTILITY FUNCTIONS *****************************************************************
 ***************************************************************************************/

int bad_input_file(const char *filename);                      /* NEEDS TESTING */
int bad_output_file(const char *filename);                     /* NEEDS TESTING */
int check_legal_double(char *s, int row);                     /* NEEDS TESTING */
int check_legal_double_modify_entry(char *s);                     /* NEEDS TESTING */
int contains_tabs(char *s);                                         /* NEEDS TESTING */
const char *get_color(double);                                       /* ADD OPTION TO DISABLE COLORS */
int is_space(char c);                                                       /* NEEDS TESTING */
int legal_amounts(Ledger *ledger);                           /* NEEDS TESTING */
int qcmp(const void *a, const void *b);                                /* NEEDS TESTING */
int str_equal(const char *s1, const char *s2);                            /* NEEDS TESTING */
void str_strip(char *s);                                                /* NEEDS TESTING */
void unique(char **s, int n, char ***ret, int *nunique);                        /* NEEDS TESTING */
void usage();                                                                        /* NEEDS TESTING */
int which(const char **);										/**NEED TO IMPLEMENT AND ADD TO CONDENSE & OTHER FUNCTIONS */


/*************************************************************************************** 
 *** FUNCTIONS TO CREATE, INITIALIZE, AND DESTROY LEDGER OBJECTS ***********************
 ***************************************************************************************/

void alloc_entries(Ledger*);                                                       /* NEEDS TESTING */
void free_ledger(Ledger*);                                                    /* NEEDS TESTING */
void free_for_retotal(Ledger*);                                                    /* NEEDS TESTING */
void get_names(Ledger *ledger);                                                    /* NEEDS TESTING */
void get_totals(Ledger *ledger);                                                    /* NEEDS TESTING */
Ledger *new_ledger();                                                    /* NEEDS TESTING */


/*************************************************************************************** 
 *** FUNCTIONS TO MODIFY LEDGER OBJECTS ************************************************
 ***************************************************************************************/

void condense(Ledger **ledger);                                                    /* NEEDS TESTING */
void insert_row(Ledger *ledger, int row);                              /* NEEDS TESTING */
void modify_entry(Ledger *ledger, int row, int col, char *next);                  /* NEEDS TESTING */
void rename_bank(Ledger *ledger, char *from, char *to);                              /* NEEDS TESTING */
void rename_credit(Ledger *ledger, char *from, char *to);                              /* NEEDS TESTING */
void rename_partition(Ledger *ledger, char *bank, char *from, char *to);              /* NEEDS TESTING */
void remove_row(Ledger *ledger, int row);                                                     /* NEEDS TESTING */
void trim_ledger(Ledger *ledger);                                                         /* NEEDS TESTING */


/*************************************************************************************** 
 *** FUNCTIONS TO MODIFY LEDGERS REPRESENTED AS STRINGS ********************************
 ***************************************************************************************/

err_t new_ledger_str();                                                      /* NEED TO IMPLEMENT ****/
void condense_str(char **s);                                                                   /* NEEDS TESTING */
void insert_row_str(char **s, int row);                                                              /* NEEDS TESTING */
void is_row_separator(char c);												/* NEED TO IMPLEMENT ****/
void is_column_separator(char c);											/* NEED TO IMPLEMENT ****/
void modify_entry_str(char **s, int row, int col, char *next);                              /* NEEDS TESTING */
void rename_bank_str(char **s, char *from, char *to);                              /* NEEDS TESTING */
void rename_credit_str(char **s, char *from, char *to);                              /* NEEDS TESTING */
void rename_partition_str(char **s, char *bank, char *from, char *to);               /* NEEDS TESTING */
void remove_row_str(char **s, int row);                                                 /* NEEDS TESTING */
void trim_ledger_str(char **s);                                                              /* NEEDS TESTING */


/*************************************************************************************** 
 *** FUNCTIONS TO PARSE INPUT INTO LEDGER OBJECTS **************************************
 ***************************************************************************************/

Ledger *get_ledger_from_filename(const char* filename);                              /* NEEDS TESTING */
Ledger *get_ledger_from_stream(FILE *fp);                                              /* NEEDS TESTING */
Ledger *get_ledger_from_string(char *s);                                             /* NEEDS TESTING */
int get_entries_from_stream(Ledger *ledger, FILE *fp);                              /* NEEDS TESTING */
int get_entries_from_string(Ledger *ledger, char *s);                              /* NEEDS TESTING */


/*************************************************************************************** 
 *** FUNCTIONS TO PRINT LEDGER OBJECTS *************************************************
 ***************************************************************************************/

err_t print_ledger_to_filename(Ledger *ledger, const char *filename);        /* NEED TO IMPLEMENT ****/
void print_ledger_to_stream(Ledger *ledger, FILE *fp);                              /* NEEDS TESTING */
char *print_ledger_to_string(Ledger *ledger);                              /* NEEDS TESTING */
void print_ledger_verbose(Ledger *ledger, FILE *fp);                              /* NEEDS TESTING */

err_t print_ledger_wrap(Ledger *in_ledger, const char *in_string,            /* NEED TO IMPLEMENT ****/
  FILE *in_stream, const char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream, const char *out_filename);

err_t print_ledger_cl(const char *s, Ledger **ledger);                     /* NEED TO IMPLEMENT ****/
err_t print_ledger_cf(const char *s, const char *filename);                    /* NEED TO IMPLEMENT ****/
err_t print_ledger_cs(const char *s, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_ledger_fc(const char *filename, char **s);                           /* NEED TO IMPLEMENT ****/
err_t print_ledger_fl(const char *filename, Ledger **ledger);                    /* NEED TO IMPLEMENT ****/
err_t print_ledger_fs(const char *filename, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_ledger_lc(Ledger *ledger, char **s);                           /* NEED TO IMPLEMENT ****/
err_t print_ledger_lf(Ledger *ledger, char *filename);                           /* NEED TO IMPLEMENT ****/
err_t print_ledger_ls(Ledger *ledger, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_ledger_sc(FILE *fp, char **s);                               /* NEED TO IMPLEMENT ****/
err_t print_ledger_sf(FILE *fp, const char *filename);                           /* NEED TO IMPLEMENT ****/
err_t print_ledger_sl(FILE *fp, Ledger **ledger);                           /* NEED TO IMPLEMENT ****/


/*************************************************************************************** 
 *** FUNCTIONS TO OUTPUT SUMMARIES OF LEDGER OBJECTS ***********************************
 ***************************************************************************************/

err_t init_summary(Ledger *ledger, char **s);								/* NEED TO IMPLEMENT */  /* ADD OPTION TO DISABLE COLORS */    /* TRIM AFTERWARDS */
err_t print_totals(float *totals, char **s); 								/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */     /* TRIM AFTERWARDS */
err_t print_partitions(char **partition, int npartition, char **s); 			/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */    /* TRIM AFTERWARDS */
err_t print_banks(Ledger *ledger, char **s);							/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */        /* TRIM AFTERWARDS */
err_t print_credits(Ledger *ledger, char **s);								/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */    /* TRIM AFTERWARDS */

err_t print_summary_to_filename(Ledger *ledger, const char *filename);     /* NEED TO IMPLEMENT ***/ /* ADD OPTION TO DISABLE COLORS */      /* TRIM AFTERWARDS */
void print_summary_to_stream(Ledger *ledger, FILE *fp);                     
char *print_summary_to_string(Ledger *ledger);
int summarize_file_to_stream(const char* filename, FILE *fp);                         /* REMOVE WHEN READY */

err_t print_summary_wrap(Ledger *in_ledger, const char *in_string,            /* NEED TO IMPLEMENT ***/
  FILE *in_stream, const char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream, const char *out_filename);

err_t print_summary_cl(const char *s, Ledger **ledger);                     /* NEED TO IMPLEMENT ****/
err_t print_summary_cf(const char *s, const char *filename);                    /* NEED TO IMPLEMENT ****/
err_t print_summary_cs(const char *s, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_summary_fc(const char *filename, char **s);                           /* NEED TO IMPLEMENT ****/
err_t print_summary_fl(const char *filename, Ledger **ledger);                    /* NEED TO IMPLEMENT ****/
err_t print_summary_fs(const char *filename, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_summary_lc(Ledger *ledger, char **s);                           /* NEED TO IMPLEMENT ****/
err_t print_summary_lf(Ledger *ledger, char *filename);                           /* NEED TO IMPLEMENT ****/
err_t print_summary_ls(Ledger *ledger, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_summary_sc(FILE *fp, char **s);                               /* NEED TO IMPLEMENT ****/
err_t print_summary_sf(FILE *fp, const char *filename);                           /* NEED TO IMPLEMENT ****/
err_t print_summary_sl(FILE *fp, Ledger **ledger);                           /* NEED TO IMPLEMENT ****/


/*************************************************************************************** 
 *** FUNCTIONS TO OUTPUT CONDENSED LEDGERS *********************************************
 ***************************************************************************************/

err_t condense_ledger_to_filename(Ledger *ledger, const char *filename);        /* NEED TO IMPLEMENT ****/
void condense_ledger_to_stream(Ledger *ledger, FILE *fp);
char *condense_ledger_to_string(Ledger *ledger);

err_t condense_wrap(Ledger *in_ledger, const char *in_string, 					/* NEED TO IMPLEMENT ***/
  FILE *in_stream, const char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream, const char *out_filename);

int condense_and_print(const char* infile, const char *outfile);                     /* REMOVE WHEN READY */

err_t print_condense_cl(const char *s, Ledger **ledger);                     /* NEED TO IMPLEMENT ****/
err_t print_condense_cf(const char *s, const char *filename);                    /* NEED TO IMPLEMENT ****/
err_t print_condense_cs(const char *s, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_condense_fc(const char *filename, char **s);                           /* NEED TO IMPLEMENT ****/
err_t print_condense_fl(const char *filename, Ledger **ledger);                    /* NEED TO IMPLEMENT ****/
err_t print_condense_fs(const char *filename, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_condense_lc(Ledger *ledger, char **s);                           /* NEED TO IMPLEMENT ****/
err_t print_condense_lf(Ledger *ledger, char *filename);                           /* NEED TO IMPLEMENT ****/
err_t print_condense_ls(Ledger *ledger, FILE *fp);                           /* NEED TO IMPLEMENT ****/

err_t print_condense_sc(FILE *fp, char **s);                               /* NEED TO IMPLEMENT ****/
err_t print_condense_sf(FILE *fp, const char *filename);                           /* NEED TO IMPLEMENT ****/
err_t print_condense_sl(FILE *fp, Ledger **ledger);                           /* NEED TO IMPLEMENT ****/


/*************************************************************************************** 
 *** TOP-LEVEL ROUTINE OF COMMAND LINE INTERFACE VERSION *******************************
 ***************************************************************************************/

int standalone(int argc, char **argv);                                       /* NEEDS TESTING */

#endif
