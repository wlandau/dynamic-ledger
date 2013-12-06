/*
 * @file ledger-txt.c
 * @author Will Landau
 * @email will.landau@gmail.com
 * @web http://will-landau.com
 * @date December 1, 2013
 * @license GPL 3.0
 * @about Ledger.txt: minimalist personal accounting software. 
 *        See README.txt for details. 
 */
 
#include <errno.h>
#include "ledger-txt.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage(){
  printf("\nUsage: to summarize the ledger,\n$ ./ledger [LEDGER_FILE]\n");
  printf("\nTo condense the ledger,\n$ ");
  printf("./ledger [INTPUT_LEDGER_FILE] [OUTTPUT_LEDGER_FILE]\n");
  printf("\nSee README.txt for details.\n");
}

/* POSITIVE MONIES GET GREEN COLORS IN OUTPUT, NEGATIVE ONES GET RED, ZEROES GET BLUE */

const char *get_color(double d){
  
  if(d > EPS)
    return POSITIVE_COLOR;
  else if(d < -EPS)
    return NEGATIVE_COLOR;
  else 
    return ZERO_COLOR;
}

/* TEXT CONTENT = 2D ARRAY OF LEDGER ENTRIES */

void alloc_text_content(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return;

  ledger->text_content = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->text_content[i] = malloc(ledger->n * sizeof(char*));
    for(j = 0; j < ledger->n; ++j)
      ledger->text_content[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }
}

/* FREE LEDGER OBJECT */

void free_for_retotal(Ledger *ledger){
  int i, j;

  if(ledger == NULL)
    return;
  
  if(ledger->partition != NULL){
    for(i = 0; i < ledger->nbank; ++i){
      if(ledger->partition[i] != NULL){
        for(j = 0; j < ledger->npartition[i]; ++j)
          if(ledger->partition[i][j] != NULL)
            free(ledger->partition[i][j]);
        free(ledger->partition[i]);
      }
    }
    free(ledger->partition);
  }
  
  if(ledger->partition_totals != NULL){
    for(i = 0; i < ledger->nbank; ++i)
      if(ledger->partition_totals[i] != NULL)
        free(ledger->partition_totals[i]);
    free(ledger->partition_totals);
  }

  if(ledger->credit != NULL){
    for(i = 0; i < ledger->ncredit; ++i)
      if(ledger->credit[i] != NULL)
        free(ledger->credit[i]);
    free(ledger->credit); 
  }

  if(ledger->credit_totals != NULL){
    for(i = 0; i < ledger->ncredit; ++i)
      if(ledger->credit_totals[i] != NULL)
        free(ledger->credit_totals[i]);
    free(ledger->credit_totals); 
  }    

  if(ledger->bank != NULL){
    for(i = 0; i < ledger->nbank; ++i)
      if(ledger->bank[i] != NULL)
        free(ledger->bank[i]);
    free(ledger->bank);
  }

  if(ledger->bank_totals != NULL){
    for(i = 0; i < ledger->nbank; ++i)
      if(ledger->bank_totals[i] != NULL)
        free(ledger->bank_totals[i]);
    free(ledger->bank_totals);
  }

  if(ledger->npartition != NULL)
    free(ledger->npartition);
}

/* FREE LEDGER OBJECT */

void free_ledger(Ledger *ledger){
  int i, j;

  if(ledger == NULL)
    return;

  if(ledger->filename != NULL)
    free(ledger->filename);
    
  if(ledger->text_content != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(ledger->text_content[i] != NULL){
        for(j = 0; j < ledger->n; ++j)
          if(ledger->text_content[i][j] != NULL)
            free(ledger->text_content[i][j]);
        free(ledger->text_content[i]);
      }
    }
    free(ledger->text_content);
  }
  
  free_for_retotal(ledger);
  free(ledger);
}

/* CHECK IF TWO STRINGS ARE EQUAL */

int str_equal(const char *s1, const char *s2){
  return !strcmp(s1, s2) && (strlen(s1) == strlen(s2));
}

/* STRING COMPARISON USED FOR qsort INSIDE unique() */

int qcmp(const void *a, const void *b){ 
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib); 
} 

/* THE LEDGER FILE IS TAB-DELIMITED, SO WE DONT WANT TABS IN ANY NEW ENTRIES */

int contains_tabs(char *s){
  int i, n = strlen(s);
  for(i = 0; i < n; ++i)
    if(s[i] == '\t')
      return i;
  return 0;
}

/* IS_SPACE... ENOUGH SAID */

int is_space(char c){
  return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == 'v');
}

/* REMOVES LEADING AND TRAILING WHITESPACE OF A STRING AS DEFINED IN IS_SPACE */

void strstrip(char *s){ /* taken from a stackoverflow forum */
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

/* CHECKS IF A CHARACTER CAN BE TRANSFORMED INTO A DOUBLE PRECISION NUMBER */

int check_legal_double(char *s, int row){
  char *testbufref, testbuf[ENTRYSIZE];
  
  errno = 0;
  strcpy(testbuf, s);
    testbufref = testbuf;
    strtod(testbuf, &testbufref); 
    if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf)){
      fprintf(stderr, "Error: bad number \"%s\" at row %d column 2.\n", 
              s, row + 1);
      fprintf(stderr, "Fix your ledger file.\n");
      return 1;   
    }
  return 0;
}

/* SPECIAL ADAPTATION OF check_legal_double() FOR modify() */

int check_legal_double_modify(char *s){
  char *testbufref, testbuf[ENTRYSIZE];
  
  if(s == NULL)
    return 1;
  
  errno = 0;
  strcpy(testbuf, s);
    testbufref = testbuf;
    strtod(testbuf, &testbufref); 
    if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf)){
      fprintf(stderr, "Error: bad number.\n");
      return 1;   
    }
  return 0;
}

/* CHECKS IF THE "AMOUNT" FIELD OF THE LEDGER
 * CAN BE TRANSFORMED INTO A DOUBLE PRECISION NUMBER */

int legal_amounts(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return 1;

  for(i = 0; i < ledger->n; ++i)
    if(check_legal_double(ledger->text_content[AMOUNT][i], i))
      return 1;

  return 0;
}

/* CHECKS IF YOU CAN OPEN THE INPUT LEDGER FILE */

int badinputfile(const char *filename){
  FILE *fp = fopen(filename, "r");
  if(fp == NULL){
    fprintf(stderr, "Error: cannot open file, %s.\nFile may not exist.\n", filename);
    return 1;
  }
  fclose(fp);
  return 0;
}

/* CHECKS IF YOU CAN OPEN THE FILE TO STORE THE CONDENSED LEDGER */

int badoutputfile(const char *filename){
  FILE *fp = fopen(filename, "w");
  if(fp == NULL){
    fprintf(stderr, 
            "Error: cannot create file, %s.\nCheck your permissions.\n", filename);
    return 1;
  }
  fclose(fp);
  return 0;
}

/* TAKES AN ARRAY OF STRINGS AND REMOVES REPEAT STRINGS */

void unique(char **s, int n, char ***ret, int *nunique){
  int i = 0, j, k;

  qsort(s, n, sizeof(char*), qcmp);

  *nunique = 1;  
  if(s[0][0] != '\0')
    ++(*nunique);

  for(j = 1; j < n; ++j){
    if(!str_equal(s[i], s[j])){
      i = j;
      ++(*nunique);
    }  
  } 
    
  *ret = malloc(*nunique * sizeof(char*));
  for(i = 0; i < *nunique; ++i)
    (*ret)[i] = calloc(ENTRYSIZE, sizeof(char));

  i = 0;
  k = 0;
    
  if(s[0][0] != '\0'){
    strcpy((*ret)[0], s[0]);
    ++k;
  }
 
  for(j = 1; j < n; ++j)
    if(!str_equal(s[i], s[j])){
      if(s[j][0] != '\0'){
        i = j;
        strcpy((*ret)[k], s[j]);
        ++k;
      }
    }  
}

/* GETS THE NAMES OF THE CREDIT ACCOUNTS, BANK ACCOUNTS, AND PARTITIONS
 * IN THE LEDGER AND STORES THEM IN A Ledger OBJECT */

void get_names(Ledger *ledger){
  int i, j;
  char **s = malloc(ledger->n * sizeof(char*));

  for(i = 0; i < ledger->n; ++i){
    s[i] = calloc(ENTRYSIZE, sizeof(char));
    strcpy(s[i], ledger->text_content[CREDIT][i]);
  }
     
  unique(s, ledger->n, &ledger->credit, &ledger->ncredit);
    
  for(i = 0; i < ledger->n; ++i)
    strcpy(s[i], ledger->text_content[BANK][i]);
  
  unique(s, ledger->n, &ledger->bank, &ledger->nbank);
  
  ledger->npartition = calloc(ledger->nbank, sizeof(int*));
  ledger->partition = malloc(ledger->nbank * sizeof(char***));
        
  for(i = 0; i < ledger->nbank; ++i){
    for(j = 0; j < ledger->n; ++j){         
      strcpy(s[j], ledger->text_content[PARTITION][j]);
      if(!str_equal(ledger->bank[i], ledger->text_content[BANK][j]))
        strcpy(s[j], NIL);
    }
     
    unique(s, ledger->n, &(ledger->partition[i]), &(ledger->npartition[i]));
  }
  
  for(i = 0; i < ledger->n; ++i)
    free(s[i]);
  free(s);
}

/* CALCULATES THE CREDIT, BANK, AND PARTITION TOTALS */

void get_totals(Ledger *ledger){
  int i, j, k;
  double amount;
  char *status;

  ledger->credit_totals = calloc(ledger->ncredit, sizeof(double*));
  for(i = 0; i < ledger->ncredit; ++i)
    ledger->credit_totals[i] = calloc(4, sizeof(double));
      
  ledger->bank_totals = calloc(ledger->nbank, sizeof(double*));  
  for(i = 0; i < ledger->nbank; ++i)
    ledger->bank_totals[i] = calloc(4, sizeof(double));
  
  ledger->partition_totals = malloc(ledger->nbank * sizeof(double*));
  for(i = 0; i < ledger->nbank; ++i)
    ledger->partition_totals[i] = calloc(ledger->npartition[i], sizeof(double));
    
  for(i = 0; i < ledger->n; ++i){
    status = ledger->text_content[STATUS][i];
    amount = atof(ledger->text_content[AMOUNT][i]);

    k = -1;
    if(str_equal(status, CREDIT_NOT_THERE_YET)){
      k = 0;
    } else if(str_equal(status, CREDIT_PENDING)){
      k = 1;
    } else if(str_equal(status, CREDIT_CLEARED)){
      k = 2;
    } 

    if(k != -1)
      for(j = 0; j < ledger->ncredit; ++j) 
        if(str_equal(ledger->text_content[CREDIT][i], ledger->credit[j])){
          ledger->credit_totals[j][k] += amount;
          break;
        }
      
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) || 
       str_equal(status, NOT_THERE_YET)){
      k = 0;
    } else if(str_equal(status, PENDING)){
      k = 1;
    } else {
      k = 2;
    }
    
    for(j = 0; j < ledger->nbank; ++j){
      if(str_equal(ledger->text_content[BANK][i], ledger->bank[j])){
        ledger->bank_totals[j][k] += amount;

        for(k = 0; k < ledger->npartition[j]; ++k){
          if(str_equal(ledger->text_content[PARTITION][i], ledger->partition[j][k])){
            ledger->partition_totals[j][k] += amount;
            break;
          }
        } 

        break;
      }
    }
  }
  
  for(j = 0; j < ledger->ncredit; ++j)
    for(k = 0; k < 3; ++k)
      ledger->credit_totals[j][I_OVERALL] += ledger->credit_totals[j][k];

  for(j = 0; j < ledger->nbank; ++j)
    for(k = 0; k < 3; ++k){
      ledger->bank_totals[j][I_OVERALL] += ledger->bank_totals[j][k];
    }  
}

/* CREATES AN EMPTY Ledger OBJECT */

Ledger *new_ledger(){
  Ledger *ledger = malloc(sizeof(Ledger));
  ledger->n = 1;
  ledger->filename = NULL;
  alloc_text_content(ledger);
  get_names(ledger);
  get_totals(ledger);   
  return ledger; 
}

/* OVERWRITES A SINGLE ENTRY IN A Ledger OBJECT AND UPDATES CREDIT, BANK,
 * AND PARTITION TOTALS ACCORDINGLY */

void modify(Ledger *ledger, int row, int col, char *next){

  char next_local[ENTRYSIZE];
  int i;

  if(ledger == NULL)
    return;

  if(row < 0 || row >= ledger->n){
    printf("Error: illegal row index in modify().\n");
    return;
  }
  
  if(col < 0 || col >= NFIELDS){
    printf("Error: illegal column index in modify().\n");
    return;
  }
  
  if(!col)
    if(check_legal_double_modify(next))
      return;
  
  strcpy(next_local, next);
  strstrip(next_local);  
  
  if((i = contains_tabs(next_local))){
    printf("Warning: entries must not contain tabs. Truncating input.\n");
    next_local[i] = '\0';
  }
  
  strcpy(ledger->text_content[col][row], next_local);

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
}

/* INSERTS A BLANK ROW */

void insert_row(Ledger *ledger, int row){
  int i, j;
  char ***x, ***tmp;
 
  if(ledger == NULL)
    return;
    
  if(row < 0 || row > ledger->n){
    printf("Error: illegal row index in insert_row().\n");
    return;
  }

  x = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    x[i] = malloc((ledger->n + 1) * sizeof(char*));
    for(j = 0; j < (ledger->n + 1); ++j)
      x[i][j] = calloc(ENTRYSIZE, sizeof(char));
  }

  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < row; ++j)
      strcpy(x[i][j], ledger->text_content[i][j]);

    strcpy(x[i][row], NIL);

    for(j = row + 1; j < (ledger->n + 1); ++j)
      strcpy(x[i][j], ledger->text_content[i][j - 1]);
  }

  tmp = ledger->text_content;
  ledger->text_content = x;
  
  if(tmp != NULL){
    for(i = 0; i < NFIELDS; ++i){
      if(tmp[i] != NULL){
        for(j = 0; j < ledger->n; ++j)
          if(tmp[i][j] != NULL)
            free(tmp[i][j]);
        free(tmp[i]);
      }
    }
    free(tmp);
  }
  
  ++(ledger->n); 
}

/* REMOVES A ROW AND UPDATES ALL TOTALS ACCORDINGLY */

void remove_row(Ledger *ledger, int row){
  int i, j, recalculate;
  
  
  if(ledger == NULL)
    return;
  
  if(row < 0 || row >= ledger->n){
    printf("Error: illegal row index in remove_row().\n");
    return;
  }
  
  if(ledger->n < 1){
    printf("Error: data already too small.\n");
    return;  
  }

  recalculate = (abs(atof(ledger->text_content[AMOUNT][row])) > EPS);

  if(ledger->n == 1){
    printf("Warning: can't remove the last row. Replacing it with a blank line.\n");
    for(i = 0; i < NFIELDS; ++i)
      strcpy(ledger->text_content[i][0], NIL);
  } else {
    for(i = 0; i < NFIELDS; ++i){
      for(j = row; j < (ledger->n - 1); ++j)
        strcpy(ledger->text_content[i][j], ledger->text_content[i][j + 1]);
      free(ledger->text_content[i][ledger->n - 1]);
    }
    --(ledger->n);
  }

  if(recalculate){
    free_for_retotal(ledger);
    get_names(ledger);
    get_totals(ledger); 
  }
}

/* REMOVES LINES (TRANSACTIONS) WITH NO CHANGE IN MONEY (AMOUNT = 0) */

void trim_ledger(Ledger *ledger){
  int i; 

  if(ledger == NULL)
    return;

  for(i = (ledger->n - 1); i >= 0; --i)
    if(abs(atof(ledger->text_content[AMOUNT][i])) < EPS)
      remove_row(ledger, i);
}

/* SAFELY RENAMES A CREDIT ACCOUNT IN THE LEDGER */

void rename_credit(Ledger *ledger, char *from, char *to){
  int i;

  if(ledger == NULL)
    return;

  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[CREDIT][i], from))
      strcpy(ledger->text_content[CREDIT][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}

/* SAFELY RENAMES A BANK ACCOUNT IN THE LEDGER */

void rename_bank(Ledger *ledger, char *from, char *to){
  int i;
  
  if(ledger == NULL)
    return;
  
  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[BANK][i], from))
      strcpy(ledger->text_content[BANK][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}

/* SAFELY RENAMES A BANK PARTITION IN THE LEDGER */

void rename_partition(Ledger *ledger, char *bank, char *from, char *to){
  int i;
  
  if(ledger == NULL)
    return;
  
  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[BANK][i], bank) && 
       str_equal(ledger->text_content[PARTITION][i], from))
      strcpy(ledger->text_content[PARTITION][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}

/* CONDENSES THE LEDGER: COLLAPSES ALL CLEARED TRANSACTIONS AND THOSE 
 * NOT MARKED AS "LOCKED" TO CALCULATE A NEW LEDGER WITH FEWER ROWS
 * THIS IS USEFUL IF YOUR LEDGER GETS TOO LONG */

void condense(Ledger **ledger){
  int i, j, k, new_n, row = 0;
  double **local_partition_totals;
  char status[ENTRYSIZE], amount[ENTRYSIZE];
  Ledger *newledger, *tmpledger;
  
  if(ledger == NULL || *ledger == NULL)
    return;

  local_partition_totals = malloc((*ledger)->nbank * sizeof(double*));
  for(i = 0; i < (*ledger)->nbank; ++i){
    local_partition_totals[i] = calloc((*ledger)->npartition[i], sizeof(double));  
    for(j = 0; j < (*ledger)->npartition[i]; ++j)
      local_partition_totals[i][j] = (*ledger)->partition_totals[i][j];
  }

  for(i = 0; i < (*ledger)->n; ++i){
    strcpy(status, (*ledger)->text_content[STATUS][i]);
    strcpy(amount, (*ledger)->text_content[AMOUNT][i]);
  
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOT_THERE_YET) || 
       str_equal(status, PENDING) ||
       str_equal(status, LOCKED)){ 

      for(j = 0; j < (*ledger)->nbank; ++j)
        if(str_equal((*ledger)->text_content[BANK][i], (*ledger)->bank[j])){
         for(k = 0; k < (*ledger)->npartition[j]; ++k){
            if(str_equal((*ledger)->text_content[PARTITION][i], (*ledger)->partition[j][k])){
              local_partition_totals[j][k] -= atof(amount);
              
              break;
            } 
          }
          break;
        }
    }
  } 
    
  newledger = malloc(sizeof(Ledger));
  newledger->filename = NULL;
  
  new_n = 0;
  for(i = 0; i < (*ledger)->n; ++i)
    new_n += (strlen((*ledger)->text_content[STATUS][i]) > 0);

  for(i = 0; i < (*ledger)->nbank; ++i)
    new_n += (*ledger)->npartition[i];

  newledger->n = new_n;
  alloc_text_content(newledger);  
  
  for(i = 0; i < (*ledger)->n; ++i){
    strcpy(status, (*ledger)->text_content[STATUS][i]);
    strcpy(amount, (*ledger)->text_content[AMOUNT][i]);
  
    if(str_equal(status, CREDIT_NOT_THERE_YET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOT_THERE_YET) || 
       str_equal(status, PENDING) || 
       str_equal(status, LOCKED)){ 
      
      if(abs(atof(amount)) > EPS){
        for(j = 0; j < NFIELDS; ++j)
          strcpy(newledger->text_content[j][row], (*ledger)->text_content[j][i]);
        ++row;
      }
    }
  } 
   
  for(i = 0; i < (*ledger)->nbank; ++i)
    for(j = 0; j < (*ledger)->npartition[i]; ++j)
      if(abs(local_partition_totals[i][j]) > EPS){
        sprintf(amount, "%0.2f", local_partition_totals[i][j]);
        strcpy(newledger->text_content[AMOUNT][row], amount);
        strcpy(newledger->text_content[BANK][row], (*ledger)->bank[i]);
        strcpy(newledger->text_content[PARTITION][row], (*ledger)->partition[i][j]);
        strcpy(newledger->text_content[DESCRIPTION][row], "condensed");
        ++row;
      }

  for(i = 0; i < (*ledger)->nbank; ++i)
    free(local_partition_totals[i]);  
  free(local_partition_totals); 

  get_names(newledger);
  get_totals(newledger); 
  trim_ledger(newledger); 
  
  tmpledger = *ledger;
  *ledger = newledger;
  free_ledger(tmpledger); 
}

/* PARSES A LEDGER FILE FROM AN INPUT STREAM */

int get_text_content_from_stream(Ledger *ledger, FILE *fp){
  int i, row, field; 
  char c, line[LINESIZE];
  
  if(ledger == NULL)
    return 1;
  
  ledger->n = -1;
  while(fgets(line, LINESIZE, fp))
    ++ledger->n;
  
  if(ledger->n < 1){
    ledger->n = 1;
    alloc_text_content(ledger);
    return 0;
  }
    
  rewind(fp);
  alloc_text_content(ledger);
  
  field = 0;
  row = 0;
  i = 0;
  
  /* ignore the header */
  fgets(line, LINESIZE, fp);
  
  /* parse the data */
  while((c = fgetc(fp)) != EOF){

    if(c== '\t'){
      if(field < ENTRYSIZE){
        i = 0;
      }
      ++field; 
    } else if(c == '\n' || c == '\r'){
      if(field < ENTRYSIZE){
        i= 0;
      }
      field = 0;
      ++row; 
    } else if(field < NFIELDS && i < ENTRYSIZE - 1){
      ledger->text_content[field][row][i] = c;
      ++i; 
    }
  }
  
  rewind(fp);
  return legal_amounts(ledger);
}

/* PARSES A LEDGER FILE FROM A STRING */

int get_text_content_from_string(Ledger *ledger, char *s){
  int i, j, row, field;
  char c;
  
  if(ledger == NULL || s == NULL)
    return 1;

  ledger->n = 1;
  for(i = 0; i < strlen(s); ++i)
    if(s[i] == '\n' || s[i] == '\r')
      ++ledger->n;
      
  alloc_text_content(ledger);

  field = 0;
  row = 0;
  j = 0;
  
  /* ignore header */
  for(i = 0; s[i] != '\n' && s[i] != '\r'; ++i);
  ++i;
  
  /* parse the data */
  for(; i < strlen(s); ++i){
    c = s[i];
      
    if(c== '\t'){
      if(field < ENTRYSIZE){
        j = 0;
      }
      ++field; 
    } else if(c == '\n' || c == '\r'){
      if(field < ENTRYSIZE){
        j = 0;
      }
      field = 0;
      ++row; 
    } else if(field < NFIELDS && j < ENTRYSIZE - 1){
      ledger->text_content[field][row][j] = c;
      ++j;
    }
  } 
   
  return legal_amounts(ledger);
}

/* CONSTRUCTS A Ledger OBJECT FROM A LEDGER FILE RECEIVED THROUGH AN INPUT STREAM */

Ledger *get_ledger_from_stream(FILE *fp){
  Ledger *ledger;
  
  if(fp == NULL)
    return NULL;

  ledger = calloc(1, sizeof(Ledger));
   
  if(get_text_content_from_stream(ledger, fp)){
    free_ledger(ledger);
    return NULL;
  } 
  
  get_names(ledger);
  get_totals(ledger);   
  
  return ledger; 
}

/* CONSTRUCTS A Ledger OBJECT GIVEN THE NAME OF A LEDGER FILE */

Ledger *get_ledger_from_filename(const char* filename){
  FILE *fp;
  Ledger *ledger = NULL;
  
  if(badinputfile(filename))
    return NULL;
  
  fp = fopen(filename, "r");
  ledger = get_ledger_from_stream(fp); 
  fclose(fp);
  
  if(ledger == NULL)
    return NULL;
    
  ledger->filename = malloc(FILENAMESIZE * sizeof(char));
  strcpy(ledger->filename, filename);

  return ledger;
}

/* CONSTRUCTS A Ledger OBJECT FROM DATA STORED AS A STRING */

Ledger *get_ledger_from_string(char *s){
  Ledger *ledger = calloc(1, sizeof(Ledger));
  if(get_text_content_from_string(ledger, s)){
    free_ledger(ledger);
    return NULL;
  }

  get_names(ledger);
  get_totals(ledger);
  return ledger;
} 

/* PRINTS A Ledger OBJECT TO A FILE STREAM */

void print_ledger_to_stream(Ledger *ledger, FILE *fp){
  int i, j;
  double amount;
  
  if(ledger == NULL || fp == NULL)
    return;
  
  fprintf(fp, "amount\tstatus\tcredit\tbank\tpartition\tdescription\n");
  for(i = 0; i < ledger->n; ++i){
    amount = atof(ledger->text_content[AMOUNT][i]);
    fprintf(fp, "%0.2f", amount);
    for(j = 1; j < NFIELDS; ++j)
      fprintf(fp, "\t%s", ledger->text_content[j][i]);
    fprintf(fp, "\n");
  }
}

/* PRINTS A Ledger OBJECT TO A STRING */

char *print_ledger_to_string(Ledger *ledger){
  char *s, entry[ENTRYSIZE], 
        header[] = "amount\tstatus\tcredit\tbank\tpartition\tdescription\n"; 
  int i, j, n = 1;
  
  if(ledger == NULL)
    return NULL;
  
  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < ledger->n; ++j){
      n += strlen(ledger->text_content[i][j]) + 1;
    }
  }
  
  s = calloc(n + strlen(header), sizeof(char));
  strcat(s, header);
  for(j = 0; j < ledger->n; ++j){
    strcat(s, ledger->text_content[AMOUNT][j]);
    
    for(i = 1; i < NFIELDS; ++i){
      strcat(s, "\t");
      
      if(strlen(ledger->text_content[i][j])){
        sprintf(entry, "%s", ledger->text_content[i][j]);
        
        strstrip(entry);
        strcat(s, entry);
      }
    }
    
    strcat(s, "\n"); 
  }
  return s;
}

/* PRINTS ALL THE DATA IN A Ledger OBJECT. OUTPUT IS UGLY. USED FOR DEBUGGING ONLY. */

void print_ledger_verbose(Ledger *ledger, FILE *fp){
  int i, j;

  if(ledger == NULL || fp == NULL)
    return;
    
  if(ledger->filename != NULL)
    fprintf(fp, "filename = %s.\n", ledger->filename);
   
  fprintf(fp, "%d rows in data\n\n", ledger->n);  
    
  fprintf(fp, "%d credit accounts:\n", ledger->ncredit);
  for(i = 0; i < ledger->ncredit; ++i){
    fprintf(fp, "\n  %s credit account:\n", ledger->credit[i]);
    fprintf(fp, "    %0.2f not arrived\n", ledger->credit_totals[i][I_NOT_THERE_YET]);
    fprintf(fp, "    %0.2f pending\n", ledger->credit_totals[i][I_PENDING]);
    fprintf(fp, "    %0.2f online balance\n", ledger->credit_totals[i][I_CLEARED]);
    fprintf(fp, "    %0.2f total\n", ledger->credit_totals[i][I_OVERALL]);
  }
  
  fprintf(fp, "\n%d bank accounts:\n", ledger->nbank);
  for(i = 0; i < ledger->nbank; ++i){
    fprintf(fp, "\n  %s bank account:\n", ledger->bank[i]);
    fprintf(fp, "    %0.2f\tnot arrived\n", ledger->bank_totals[i][I_NOT_THERE_YET]);
    fprintf(fp, "    %0.2f\tpending\n", ledger->bank_totals[i][I_PENDING]);
    fprintf(fp, "    %0.2f\tonline balance\n", ledger->bank_totals[i][I_CLEARED]);
    fprintf(fp, "    %0.2f\ttotal\n\n", ledger->bank_totals[i][I_OVERALL]);
    fprintf(fp, "    %d partitions\n", ledger->npartition[i]);
    for(j = 0; j < ledger->npartition[i]; ++j){
      if(strlen(ledger->partition[i][j]))
        fprintf(fp, "      %0.2f\t%s\n", ledger->partition_totals[i][j],
                                        ledger->partition[i][j]);
      else
        fprintf(fp, "      %0.2f\tunpartitioned\n", ledger->partition_totals[i][j]);
    }
  }  

  fprintf(fp, "\n");
  print_ledger_to_stream(ledger, fp);
}

/* PRINTS A PRETTY SUMMARY OF A Ledger OBJECT TO A FILE STREAM */

void print_summary_to_stream(Ledger *ledger, FILE *fp){
  int i, j, l0, l1, l2, any = 0, anyp = 0;

  if(ledger == NULL || fp == NULL)
    return;

  fprintf(fp, "%s", NORMAL_COLOR);

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->credit_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->credit_totals[i][I_CLEARED]) > EPS);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credit[i]))
        fprintf(fp,"\nCredit account: %s\n\n", ledger->credit[i]);
      else
        fprintf(fp,"\nCredit account with no name:\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", 
                  get_color(ledger->credit_totals[i][I_NOT_THERE_YET]), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", 
                  get_color(ledger->credit_totals[i][I_PENDING]), 
                  ledger->credit_totals[i][I_PENDING], NORMAL_COLOR);
        fprintf(fp, "\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", 
                get_color(ledger->credit_totals[i][I_CLEARED]),
                ledger->credit_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  get_color(ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED]),
                  ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED],
                  NORMAL_COLOR);
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                get_color(ledger->credit_totals[i][I_OVERALL]),
                ledger->credit_totals[i][I_OVERALL], NORMAL_COLOR);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                get_color(ledger->credit_totals[i][I_OVERALL]), 
                ledger->credit_totals[i][I_OVERALL], NORMAL_COLOR); 
        fprintf(fp,"                                All charges cleared.\n");
      }
    }
  }
          
  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->bank_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->bank_totals[i][I_CLEARED]) > EPS); 
  
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->bank[i]))
        fprintf(fp,"\nBank account: %s\n\n", ledger->bank[i]);
      else 
        fprintf(fp,"\nBank account with no name\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", 
                  get_color(ledger->bank_totals[i][I_NOT_THERE_YET]),
                  ledger->bank_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", 
                  get_color(ledger->bank_totals[i][I_PENDING]), 
                  ledger->bank_totals[i][I_PENDING], NORMAL_COLOR); 
        fprintf(fp,"\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", 
                get_color(ledger->bank_totals[i][I_CLEARED]),
                ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  get_color(ledger->bank_totals[i][I_PENDING] 
                + ledger->bank_totals[i][I_CLEARED]),
                  ledger->bank_totals[i][I_PENDING] 
                + ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                get_color(ledger->bank_totals[i][I_OVERALL]),
                ledger->bank_totals[i][I_OVERALL], NORMAL_COLOR);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", 
                get_color(ledger->bank_totals[i][I_OVERALL]),
                ledger->bank_totals[i][I_OVERALL], NORMAL_COLOR);
        fprintf(fp,"                                All charges cleared.\n");
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > EPS){
        if(strlen(ledger->partition[i][j])){
          if(!anyp){
            fprintf(fp,"\n          Partitions:\n");
            ++anyp;
          }
          fprintf(fp,"%s%30.2f%s  %s\n", get_color(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], NORMAL_COLOR, ledger->partition[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][I_CLEARED]) > EPS){
          if(!j) fprintf(fp, "\n");
          fprintf(fp,"%s%30.2f%s  unpartitioned\n", get_color(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], NORMAL_COLOR);
        }
      } 
  }
  
  if(any)
    fprintf(fp,"\n");
}

/* PRINTS A PRETTY SUMMARY OF A Ledger OBJECT TO A STRING */

char *print_summary_to_string(Ledger *ledger){
  int i, j, l0, l1, l2, any = 0, anyp = 0;
  
  char *s;

  if(ledger == NULL)
    return NULL;
    
  s = calloc(ledger->n * NFIELDS * ENTRYSIZE, sizeof(char));

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->credit_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->credit_totals[i][I_CLEARED]) > EPS);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credit[i]))
        sprintf(s,"%s\nCredit account: %s\n\n", s, ledger->credit[i]);
      else
        sprintf(s,"%s\nCredit account with no name:\n\n", s);
 
      if(l0 || l1){
      
        sprintf(s,"%s          Delayed money:\n",s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, 
                  get_color(ledger->credit_totals[i][I_NOT_THERE_YET]), 
                  ledger->credit_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n", s, 
                  get_color(ledger->credit_totals[i][I_PENDING]), 
                  ledger->credit_totals[i][I_PENDING], NORMAL_COLOR);

        sprintf(s, "%s\n          Balances:\n", s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, 
                get_color(ledger->credit_totals[i][I_CLEARED]),
                ledger->credit_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  get_color(ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED]),
                  ledger->credit_totals[i][I_PENDING] 
                + ledger->credit_totals[i][I_CLEARED],
                  NORMAL_COLOR);
        sprintf(s,"%s%s%30.2f%s  true balance\n",s, 
                get_color(ledger->credit_totals[i][I_OVERALL]),
                ledger->credit_totals[i][I_OVERALL], NORMAL_COLOR);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s, 
                get_color(ledger->credit_totals[i][I_OVERALL]), 
                ledger->credit_totals[i][I_OVERALL], NORMAL_COLOR); 
        sprintf(s,"%s                                All charges cleared.\n", s);
      }
    }
  }     
          
  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][I_NOT_THERE_YET]) > EPS);
    l1 = (abs(ledger->bank_totals[i][I_PENDING]) > EPS);
    l2 = (abs(ledger->bank_totals[i][I_CLEARED]) > EPS); 
  
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->bank[i]))
        sprintf(s,"%s\nBank account: %s\n\n", s, ledger->bank[i]);
      else 
        sprintf(s,"%s\nBank account with no name\n\n", s);
 
      if(l0 || l1){
        sprintf(s,"%s          Delayed money:\n", s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, get_color(ledger->bank_totals[i][I_NOT_THERE_YET]),
                  ledger->bank_totals[i][I_NOT_THERE_YET], NORMAL_COLOR); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n",s, get_color(ledger->bank_totals[i][I_PENDING]), 
                  ledger->bank_totals[i][I_PENDING], NORMAL_COLOR); 
        sprintf(s,"%s\n          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, get_color(ledger->bank_totals[i][I_CLEARED]),
                ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  get_color(ledger->bank_totals[i][I_PENDING] + ledger->bank_totals[i][I_CLEARED]),
                  ledger->bank_totals[i][I_PENDING] + ledger->bank_totals[i][I_CLEARED], NORMAL_COLOR);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,get_color(ledger->bank_totals[i][I_OVERALL]),
                ledger->bank_totals[i][I_OVERALL], NORMAL_COLOR);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,get_color(ledger->bank_totals[i][I_OVERALL]),
                ledger->bank_totals[i][I_OVERALL], NORMAL_COLOR);
        sprintf(s,"%s                                All charges cleared.\n",s);
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > EPS){
        if(strlen(ledger->partition[i][j])){
          if(!anyp){
            sprintf(s,"%s\n          Partitions:\n",s);
            ++anyp;
          }
          sprintf(s,"%s%s%30.2f%s  %s\n",s, get_color(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], NORMAL_COLOR, ledger->partition[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][I_CLEARED]) > EPS){
          if(!j) sprintf(s, "%s\n",s);
          sprintf(s,"%s%s%30.2f%s  unpartitioned\n",s, get_color(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], NORMAL_COLOR);
        }
      } 
  }
  
  if(any)
    sprintf(s,"%s\n",s);
    
  return s;
}

/* PRINTS A RAW STRING LEDGER TO A FILE STREAM */

void print_ledger_to_stream_str(char *s, FILE *fp){
  Ledger *ledger = get_ledger_from_string(s);
  
  if(ledger == NULL)
    return;
  
  print_ledger_to_stream(ledger, fp);
  free_ledger(ledger);
} 

/* PRINTS A SUMMARY OF A RAW STRING LEDGER TO A FILE STREAM */

void print_summary_to_stream_str(char *s, FILE *fp){
  Ledger *ledger = get_ledger_from_string(s);
  
  if(ledger == NULL)
    return;
  
  print_summary_to_stream(ledger, fp);
  free_ledger(ledger);
} 

/* PRINTS A RAW STRING LEDGER TO ANOTHER RAW STRING */
 
char *print_summary_to_string_str(char *s){
  char *s2;
  Ledger *ledger = get_ledger_from_string(s);
  
  if(ledger == NULL)
    return NULL;
  
  s2 = print_summary_to_string(ledger);
  
  if(s2 == NULL)
    return NULL;
  
  free_ledger(ledger);
  return s2;
} 

/* LIKE modify(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void modify_str(char **s, int row, int col, char *next){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  modify(ledger, row, col, next);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}

/* LIKE insert_row(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void insert_row_str(char **s, int row){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  insert_row(ledger, row);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}  

/* LIKE remove_row(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void remove_row_str(char **s, int row){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  remove_row(ledger, row);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}  

/* LIKE trim_ledger(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */
 
void trim_ledger_str(char **s){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  trim_ledger(ledger);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
} 

/* LIKE rename_credit(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void rename_credit_str(char **s, char *from, char *to){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  rename_credit(ledger, from, to);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}

/* LIKE rename_bank(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void rename_bank_str(char **s, char *from, char *to){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  rename_bank(ledger, from, to);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}

/* LIKE rename_partition(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void rename_partition_str(char **s, char *bank, char *from, char *to){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  rename_partition(ledger, bank, from, to);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
}

/* LIKE condense(), EXCEPT WITH A THE LEDGER INPUT AS A RAW STRING */

void condense_str(char **s){
  char *s2, *tmp;
  Ledger *ledger;
  
  if(s == NULL || *s == NULL)
    return;
  
  ledger = get_ledger_from_string(*s);
  
  if(ledger == NULL)
    return;
  
  condense(&ledger);
  s2 = print_ledger_to_string(ledger);
  free_ledger(ledger);
  
  tmp = *s;
  *s = s2;
  s2 = tmp;
  free(s2);
} 

/* IF THE PROGRAM IS GIVEN ONE FILENAME AS INPUT, THE PROGRAM USES THIS FUNCTION
 * TO READ THE FILE INTO A LEDGER OBJECT AND THEN PRINT A SUMMARY OF THAT 
 * LEDGER TO A FILE STREAM */

int summarize_file_to_stream(const char* filename, FILE *fp){
  Ledger *ledger = get_ledger_from_filename(filename);
  int ind = (ledger == NULL);
  
  if(ind)
    return 1;

  print_summary_to_stream(ledger, fp);
  
  free_ledger(ledger);
  return 0;
}

/* IF THE PROGRAM IS GIVEN TWO INPUT FILE NAMES, THE PROGRAM USES THIS FUNCTION
 * TO READ THE FIRST FILENAME AS AN INPUT LEDGER. THEN, IT CONDENSES THE LEDGER
 * WITH condense() AND WRITES THE CONDENSED LEDGER AS OUTPUT TO THE SECOND FILE. */

int condense_and_print(const char* infile, const char *outfile){
  FILE *fp;
  Ledger *ledger;
  
  if(badinputfile(infile))
    return 1;
  
  ledger = get_ledger_from_filename(infile);
  if(ledger == NULL){
    printf("Failed to read ledger.\n");
    return 1;
  }  
  
  condense(&ledger);
      
  if(!badoutputfile(outfile)){
    fp = fopen(outfile, "w");
    print_ledger_to_stream(ledger, fp);
    fclose(fp);
  }
  
  free_ledger(ledger);
  return 0;
}
 
/* MAIN WORKHORSE OF THE STANDALONE C VERSION OF Ledger.txt. IT DOES 
 * SUMMARY IF GIVEN AN INPUT FILE NAME AND condense() IF GIVEN BOTH
 * INPUT AND OUTPUT FILE NAMES. */
 
int standalone(int argc, char **argv){
  if(argc == 2){
    if(summarize_file_to_stream(argv[1], stdout)){
      printf("Exiting.\n");
      return 1;
    }
  } else if(argc == 3){
    if(condense_and_print(argv[1], argv[2])){
      printf("No output produced.\nExiting.\n");
      return 1;
    }
  } else{
    usage(); 
  }

  return 0;
}

int main(int argc, char **argv){ 
  return standalone(argc, argv) ? EXIT_FAILURE : EXIT_SUCCESS;
}
