#ifndef LEDGER_H
#define LEDGER_H

/***
 *** @file ledger.h
 *** @author Will Landau
 *** @email will.landau@gmail.com
 *** @web http://will-landau.com
 *** @date December 1, 2013
 *** @license GPL 3.0
 *** @about Dynamic Ledger: minimalist personal accounting software. 
 ***        See README.txt for details. 
 ***/

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>


/*************************************************************************************** 
 *** INDICES FOR CREDIT AND BANK TOTALS ************************************************
 ***************************************************************************************/

#define I_NOT_THERE_YET   0
#define I_PENDING         1
#define I_CLEARED         2
#define I_PENDING_BAL     3	
#define I_OVERALL_BAL     4													/* NEED TO IMPLEMENT WHEN ALLOCATING/CALCULATING TOTALS AND SUMMARIZING */
#define N_TOTALS          5														/* NEED TO IMPLEMENT WHEN ALLOCATING/CALCULATING TOTALS AND SUMMARIZING */


/*************************************************************************************** 
 *** RETURN CODES **********************************************************************
 ***************************************************************************************/

#define LSUCCESS   0
#define LFAILURE   1

#define LNO    0
#define LYES   1

#define NO_INDEX   -1


/*************************************************************************************** 
 *** MISC INTERNAL PARAMETERS **********************************************************
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
typedef int bool_t;
typedef int index_t;
typedef  char* color_t;

typedef struct {
  char *filename, **banks, **credits, ***partitions, ***entries;
  int nrows, nbanks, ncredits, *npartitions; 
  double **bank_totals, **credit_totals, **partition_totals;            
} Ledger;


/*************************************************************************************** 
 *** UTILITY FUNCTIONS *****************************************************************
 ***************************************************************************************/

bool_t input_file( char *filename);
bool_t output_file( char *filename); 
bool_t legal_double(char *s); 
bool_t col_delim_char(char c);   
index_t col_delim_str(char *s);                                        
bool_t row_delim_char(char c);
index_t row_delim_str(char *s);
color_t color(double);            
bool_t space(char c);                     
bool_t legal_amounts(Ledger *ledger); 
bool_t legal_status_code(char *s); 
bool_t legal_status_codes(Ledger *ledger); 
int qcmp(const void *a, const void *b);                                     
bool_t str_equal(const char *s1, const char *s2); 
void str_strip(char *s);     
err_t unique(char **s, int n, char ***ret, int *nunique);
void usage();
index_t which(char **s,  char *find, int n);
index_t which_bank_total(char *status);
index_t which_credit_total(char *status);
bool_t locked(char *status);

/*************************************************************************************** 
 *** FUNCTIONS TO CREATE, INITIALIZE, AND DESTROY LEDGER OBJECTS ***********************
 ***************************************************************************************/

err_t alloc_entries(Ledger*);
err_t alloc_totals(Ledger*);
void free_ledger(Ledger**); 
void free_for_retotal(Ledger*);
err_t get_names(Ledger *ledger);
err_t get_totals(Ledger *ledger);
err_t new_ledger(Ledger **ledger); 


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
err_t strip_ledger(Ledger *ledger);     
err_t repartition(Ledger *ledger, char *bank, char **partitions, double *amounts);					/* NEED TO IMPLEMENT ****/
err_t repartition_percent(Ledger *ledger, char *bank, char **partitions, double *percentages);					/* NEED TO IMPLEMENT ****/

/*************************************************************************************** 
 *** FUNCTIONS TO MODIFY LEDGERS REPRESENTED AS STRINGS ********************************
 ***************************************************************************************/

err_t new_ledger_str();                                                      /* NEED TO IMPLEMENT ****/
void condense_str(char **s);                                                                   /* NEEDS TESTING */
void insert_row_str(char **s, int row);                                                              /* NEEDS TESTING */
void modify_entry_str(char **s, int row, int col, char *next);                              /* NEEDS TESTING */
void rename_bank_str(char **s, char *from, char *to);                              /* NEEDS TESTING */
void rename_credit_str(char **s, char *from, char *to);                              /* NEEDS TESTING */
void rename_partition_str(char **s, char *bank, char *from, char *to);               /* NEEDS TESTING */
void remove_row_str(char **s, int row);                                                 /* NEEDS TESTING */
void trim_ledger_str(char **s);                                                              /* NEEDS TESTING */
err_t repartition_str(char **s, char *bank, char **partitions, double *amounts);					/* NEED TO IMPLEMENT ****/
err_t repartition_percent_str(char **s, char *bank, char **partitions, double *percentages);					/* NEED TO IMPLEMENT ****/

/*************************************************************************************** 
 *** FUNCTIONS TO PARSE INPUT INTO LEDGER OBJECTS **************************************
 ***************************************************************************************/

void parse_char(Ledger *ledger, char c, int *char_index, int *field, int *row);
err_t get_entries_from_filename(Ledger *ledger, char *filename); 
err_t get_entries_from_stream(Ledger *ledger, FILE *fp); 
err_t get_entries_from_string(Ledger *ledger, char *s);  
err_t get_ledger(Ledger **ledger, char* filename, FILE *fp, char *str);


/*************************************************************************************** 
 *** FUNCTIONS TO PRINT LEDGER OBJECTS *************************************************
 ***************************************************************************************/

err_t print_ledger_to_filename(Ledger *ledger,  char *filename);        /* NEED TO IMPLEMENT ****/
err_t print_ledger_to_stream(Ledger *ledger, FILE *fp);                              /* NEEDS TESTING */
err_t print_ledger_to_string(Ledger *ledger, char **s);                              /* NEEDS TESTING */
void print_ledger_verbose(Ledger *ledger, FILE *fp);

err_t print_ledger_wrap(Ledger *in_ledger,  char *in_string,            /* NEED TO IMPLEMENT ****/
  FILE *in_stream,  char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream,  char *out_filename);


/*************************************************************************************** 
 *** FUNCTIONS TO OUTPUT SUMMARIES OF LEDGER OBJECTS ***********************************
 ***************************************************************************************/

err_t init_summary(Ledger *ledger, char **s);								/* NEED TO IMPLEMENT */  /* ADD OPTION TO DISABLE COLORS */    /* TRIM AFTERWARDS */
err_t print_totals(float *totals, char **s); 								/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */     /* TRIM AFTERWARDS */
err_t print_partitions(char **partition, int npartition, char **s); 			/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */    /* TRIM AFTERWARDS */
err_t print_banks(Ledger *ledger, char **s);							/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */        /* TRIM AFTERWARDS */
err_t print_credits(Ledger *ledger, char **s);								/* NEED TO IMPLEMENT ***/  /* ADD OPTION TO DISABLE COLORS */    /* TRIM AFTERWARDS */

err_t print_summary_to_filename(Ledger *ledger,  char *filename);     /* NEED TO IMPLEMENT ***/ /* ADD OPTION TO DISABLE COLORS */      /* TRIM AFTERWARDS */
void print_summary_to_stream(Ledger *ledger, FILE *fp);                     
char *print_summary_to_string(Ledger *ledger);
int summarize_file_to_stream(char* filename, FILE *fp);                         /* REMOVE WHEN READY */

err_t print_summary_wrap(Ledger *in_ledger,  char *in_string,            /* NEED TO IMPLEMENT ***/
  FILE *in_stream,  char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream,  char *out_filename);


/*************************************************************************************** 
 *** FUNCTIONS TO OUTPUT CONDENSED LEDGERS *********************************************
 ***************************************************************************************/

err_t condense_ledger_to_filename(Ledger *ledger,  char *filename);        /* NEED TO IMPLEMENT ****/
void condense_ledger_to_stream(Ledger *ledger, FILE *fp);
char *condense_ledger_to_string(Ledger *ledger);

err_t condense_wrap(Ledger *in_ledger,  char *in_string, 					/* NEED TO IMPLEMENT ***/
  FILE *in_stream,  char *in_filename, Ledger *out_ledger, 
  char **out_string, FILE *out_stream,  char *out_filename);

int condense_and_print( char* infile,  char *outfile);                     /* REMOVE WHEN READY */


/*************************************************************************************** 
 *** TOP-LEVEL ROUTINE OF COMMAND LINE INTERFACE VERSION *******************************
 ***************************************************************************************/

int standalone(int argc, char **argv);                                       /* NEEDS TESTING */

#endif
