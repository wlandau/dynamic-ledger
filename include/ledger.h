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
#define I_OVERALL         3
#define I_PENDING_BAL     4														/* NEED TO IMPLEMENT WHEN ALLOCATING/CALCULATING TOTALS AND SUMMARIZING */
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
typedef const char* color_t;

typedef struct {
  char *filename, **banks, **credits, ***partitions, ***entries;
  int nrows, nbanks, ncredits, *npartitions; 
  double **bank_totals, **credit_totals, **partition_totals;            
} Ledger;


/*************************************************************************************** 
 *** UTILITY FUNCTIONS *****************************************************************
 ***************************************************************************************/

bool_t input_file(const char *filename);
bool_t output_file(const char *filename); 
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
index_t which(char **s, const char *find, int n);


/*************************************************************************************** 
 *** FUNCTIONS TO CREATE, INITIALIZE, AND DESTROY LEDGER OBJECTS ***********************
 ***************************************************************************************/

err_t alloc_entries(Ledger*);
void free_ledger(Ledger*);                                                    /* NEEDS TESTING */
void free_for_retotal(Ledger*);                                                    /* NEEDS TESTING */
void get_names(Ledger *ledger);                                                    /* NEEDS TESTING */
void get_totals(Ledger *ledger);                                                    /* NEEDS TESTING */
Ledger *new_ledger(); 


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
Ledger *get_ledger_from_filename(const char* filename);                              /* NEEDS TESTING */
Ledger *get_ledger_from_stream(FILE *fp);                                              /* NEEDS TESTING */
Ledger *get_ledger_from_string(char *s);                                             /* NEEDS TESTING */


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
