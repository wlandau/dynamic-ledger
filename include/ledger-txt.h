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

#define AMOUNT        0   /*** TRANSACTION AMOUNTS ************/
#define STATUS        1   /*** TRANSACTION STATUS CODES *******/
#define CREDIT        2   /*** NAMES OF CREDIT ACCOUNTS *******/
#define BANK          3   /*** NAMES OF BANK ACCOUNTS *********/       
#define PARTITION     4   /*** NAMES OF BANK PARTITIONS *******/
#define DESCRIPTION   5   /*** DESCRIPTIONS OF TRANSACTIONS ***/


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


/*************************************************************************************** 
 *** INTERNAL PARAMETERS ***************************************************************
 ***************************************************************************************/

#define ENTRYSIZE      256
#define EPS            0.004
#define FFAIL          1
#define FILENAMESIZE   256
#define FSUCCEED       0
#define LINESIZE       4096
#define NFIELDS        6
#define NIL            "\0"


/*************************************************************************************** 
 *** DATA TYPES ************************************************************************
 ***************************************************************************************/

typedef int err_t;

typedef struct {
  char *filename, **bank, **credit, ***partition, ***text_content;
  int n, nbank, ncredit, *npartition;
  double **bank_totals, **credit_totals, **partition_totals;
} Ledger;


/*************************************************************************************** 
 *** UTILITY FUNCTIONS *****************************************************************
 ***************************************************************************************/

int bad_input_file(const char *filename);
int bad_output_file(const char *filename);
int check_legal_double(char *s, int row);
int check_legal_double_modify_entry(char *s);
int contains_tabs(char *s);
const char *get_color(double);
int is_space(char c);
int legal_amounts(Ledger *ledger);
int qcmp(const void *a, const void *b);
int str_equal(const char *s1, const char *s2);
void str_strip(char *s);
void unique(char **s, int n, char ***ret, int *nunique);
void usage();


/*************************************************************************************** 
 *** FUNCTIONS FOR CREATING, POPULATING, AND DESTROYING LEDGER OBJECTS *****************
 ***************************************************************************************/

void alloc_text_content(Ledger*);
void free_ledger(Ledger*);
void free_for_retotal(Ledger*);
void get_names(Ledger *ledger);
void get_totals(Ledger *ledger);
Ledger *new_ledger();


/*************************************************************************************** 
 *** FUNCTIONS FOR MODIFYING LEDGER OBJECTS ********************************************
 ***************************************************************************************/

void condense(Ledger **ledger);
void insert_row(Ledger *ledger, int row);
void modify_entry(Ledger *ledger, int row, int col, char *next);
void rename_bank(Ledger *ledger, char *from, char *to);
void rename_credit(Ledger *ledger, char *from, char *to);
void rename_partition(Ledger *ledger, char *bank, char *from, char *to);
void remove_row(Ledger *ledger, int row);
void trim_ledger(Ledger *ledger);


/*************************************************************************************** 
 *** FUNCTIONS FOR MODIFYING LEDGERS REPRESENTED AS STRINGS ****************************
 ***************************************************************************************/

err_t new_ledger_str();                                                      /* NEED TO IMPLEMENT ****/
void condense_str(char **s);
void insert_row_str(char **s, int row);
void modify_entry_str(char **s, int row, int col, char *next);
void rename_bank_str(char **s, char *from, char *to);
void rename_credit_str(char **s, char *from, char *to);
void rename_partition_str(char **s, char *bank, char *from, char *to);
void remove_row_str(char **s, int row);
void trim_ledger_str(char **s);


/*************************************************************************************** 
 *** FUNCTIONS PARSING INPUT INTO LEDGER OBJECTS ***************************************
 ***************************************************************************************/

Ledger *get_ledger_from_filename(const char* filename);
Ledger *get_ledger_from_stream(FILE *fp);
Ledger *get_ledger_from_string(char *s);
int get_text_content_from_stream(Ledger *ledger, FILE *fp);
int get_text_content_from_string(Ledger *ledger, char *s);


/*************************************************************************************** 
 *** FUNCTIONS FOR PRINTING LEDGER OBJECTS *********************************************
 ***************************************************************************************/

err_t print_ledger_to_filename(Ledger *ledger, const char *filename);        /* NEED TO IMPLEMENT ****/
void print_ledger_to_stream(Ledger *ledger, FILE *fp);
char *print_ledger_to_string(Ledger *ledger);
void print_ledger_verbose(Ledger *ledger, FILE *fp);

err_t print_ledger_wrap(Ledger *in_ledger, const char *in_string, 
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

err_t print_summary_to_filename(Ledger *ledger, const char *filename);     /* NEED TO IMPLEMENT ***/
void print_summary_to_stream(Ledger *ledger, FILE *fp);                     
char *print_summary_to_string(Ledger *ledger);
int summarize_file_to_stream(const char* filename, FILE *fp);                         /* REMOVE WHEN READY */

err_t print_summary_wrap(Ledger *in_ledger, const char *in_string, 
  FILE *in_stream, const char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream, const char *out_filename);

/*************************************************************************************** 
 *** FUNCTIONS TO OUTPUT CONDENSED LEDGERS *********************************************
 ***************************************************************************************/

err_t condense_ledger_to_filename(Ledger *ledger, const char *filename);        /* NEED TO IMPLEMENT ****/
void condense_ledger_to_stream(Ledger *ledger, FILE *fp);
char *condense_ledger_to_string(Ledger *ledger);

err_t condense_wrap(Ledger *in_ledger, const char *in_string, 
  FILE *in_stream, const char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream, const char *out_filename);

int condense_and_print(const char* infile, const char *outfile);                     /* REMOVE WHEN READY */


/*************************************************************************************** 
 *** TOP-LEVEL ROUTINE OF COMMAND LINE INTERFACE VERSION *******************************
 ***************************************************************************************/

int standalone(int argc, char **argv);

#endif
