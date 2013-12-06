/*
 * @file ledger-txt.h
 * @author Will Landau
 * @email will.landau@gmail.com
 * @web http://will-landau.com
 * @date December 1, 2013
 * @license GPL 3.0
 * @about Ledger.txt: minimalist personal accounting software. 
 *        See README.txt for details. 
 */

#ifndef LEDGER_TXT_H
#define LEDGER_TXT_H

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* USER-DEFINED: COLUMN INDEX FOR EACH FIELD IN THE TEXT FILE */

#define AMOUNT 0
#define STATUS 1
#define CREDIT 2
#define BANK 3
#define PARTITION 4
#define DESCRIPTION 5

/* TRANSACTION STATUS CODES */

#define CREDIT_NOTTHEREYET "cn"
#define CREDIT_PENDING "cp"
#define CREDIT_CLEARED "c"
#define NOTTHEREYET "n"
#define PENDING "p"
#define LOCKED "l"

/* INDICES FOR CREDIT AND BANK TOTALS */

#define I_NOTTHEREYET 0
#define I_PENDING 1
#define I_CLEARED 2
#define I_OVERALL 3

/* COMPUTATIONAL PARAMETERS (MEMORY SIZES, ETC) */

#define EPS 0.004
#define NIL "\0"
#define NFIELDS 6
#define FIELDSIZE 256
#define LINESIZE 4096
#define FILENAMESIZE 256

/* COLOR CODES FOR OUTPUT */

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

/* BASIC DATA STRUCTURE: ALMOST EVERYTHING IS IN A Ledger OBJECT */

typedef struct {
  char *filename, **credit, **bank, ***partition, ***text_content;
  int n, ncredit, nbank, *npartition;
  double **credit_totals, **bank_totals, **partition_totals;
} Ledger;

/* ALL FUNCTIONS */

void usage();
const char *ksgn(double);

void alloc_text_content(Ledger*);
void free_for_retotal(Ledger*);
void free_ledger(Ledger*);

int str_equal(const char *s1, const char *s2);
int qcmp(const void *a, const void *b);
int contains_tabs(char *s);
int is_space(char c);
void strstrip(char *s);
int check_legal_double(char *s, int row);
int check_legal_double_modify(char *s);
int legal_amounts(Ledger *ledger);

int badinputfile(const char *filename);
int badoutputfile(const char *filename);

void unique(char **s, int n, char ***ret, int *nunique);
void get_names(Ledger *ledger);
void get_totals(Ledger *ledger);

Ledger *new_ledger();

void modify(Ledger *ledger, int row, int col, char *next);
void insert_row(Ledger *ledger, int row);
void remove_row(Ledger *ledger, int row);
void trim_ledger(Ledger *ledger);
void rename_credit(Ledger *ledger, char *from, char *to);
void rename_bank(Ledger *ledger, char *from, char *to);
void rename_partition(Ledger *ledger, char *bank, char *from, char *to);
void condense(Ledger **ledger);

int get_text_content_from_stream(Ledger *ledger, FILE *fp);
int get_text_content_from_string(Ledger *ledger, char *s);
Ledger *get_ledger_from_stream(FILE *fp);
Ledger *get_ledger_from_filename(const char* filename);
Ledger *get_ledger_from_string(char *s);
void print_ledger_to_stream(Ledger *ledger, FILE *fp);
char *print_ledger_to_string(Ledger *ledger);
void print_ledger_verbose(Ledger *ledger, FILE *fp);
void print_summary_to_stream(Ledger *ledger, FILE *fp);

char *print_summary_to_string(Ledger *ledger);
void print_ledger_to_stream_str(char *s, FILE *fp);
char *print_summary_to_string_str(char *s);
void modify_str(char **s, int row, int col, char *next);
void insert_row_str(char **s, int row);
void remove_row_str(char **s, int row);
void trim_ledger_str(char **s);
void rename_credit_str(char **s, char *from, char *to);
void rename_bank_str(char **s, char *from, char *to);
void rename_partition_str(char **s, char *bank, char *from, char *to);
void condense_str(char **s);
int summarize_file_to_stream(const char* filename, FILE *fp);
int condense_and_print(const char* infile, const char *outfile);
int standalone(int argc, char **argv);

#endif