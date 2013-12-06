/*
 * @file ledger.c
 * @author Will Landau
 * @email will.landau@gmail.com
 * @web http://will-landau.com
 * @date December 1, 2013
 * @license GPL 3.0
 * @about Personal accounting software. See README.txt for details. 
 */
 
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CREDIT_NOTTHEREYET "cn"
#define CREDIT_PENDING "cp"
#define CREDIT_CLEARED "c"
#define NOTTHEREYET "n"
#define PENDING "p"
#define LOCKED "l"

#define NIL "\0"
#define NFIELDS 6
#define FIELDSIZE 256
#define LINESIZE 4096
#define FILENAMESIZE 256

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

const char *ksgn(double d){
  double eps = 0.004;
  if(d > eps)
    return KGRN;
  else if(d < -eps)
    return KRED;
  else 
    return KBLU;
}

typedef struct {
  char *filename, **credit, **bank, ***partition, ***text_content;
  int n, ncredit, nbank, *npartition;
  double **credit_totals, **bank_totals, **partition_totals;
} Ledger;

void usage(){
  printf("\nUsage: to summarize the ledger,\n$ ./ledger [LEDGER_FILE]\n");
  printf("\nTo condense the ledger,\n$ ./ledger [INTPUT_LEDGER_FILE] [OUTTPUT_LEDGER_FILE]\n");
  printf("\nSee README.txt for details.\n");
}

void print_ledger_to_stream(Ledger *ledger, FILE *fp){
  int i, j;
  double amount;
  
  if(ledger == NULL || fp == NULL)
    return;
  
  fprintf(fp, "amount\tstatus\tcredit\tbank\tpartition\tdescription\n");
  for(i = 0; i < ledger->n; ++i){
    amount = atof(ledger->text_content[0][i]);
    fprintf(fp, "%0.2f", amount);
    for(j = 1; j < NFIELDS; ++j)
      fprintf(fp, "\t%s", ledger->text_content[j][i]);
    fprintf(fp, "\n");
  }
}

void alloc_text_content(Ledger *ledger){
  int i, j;
  
  if(ledger == NULL)
    return;

  ledger->text_content = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->text_content[i] = malloc(ledger->n * sizeof(char*));
    for(j = 0; j < ledger->n; ++j)
      ledger->text_content[i][j] = calloc(FIELDSIZE, sizeof(char));
  }
}

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

int badinputfile(const char *filename){
  FILE *fp = fopen(filename, "r");
  if(fp == NULL){
    fprintf(stderr, "Error: cannot open file, %s.\nFile may not exist.\n", filename);
    return 1;
  }
  fclose(fp);
  return 0;
}

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

int qcmp(const void *a, const void *b){ 
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib); 
} 

int str_equal(const char *s1, const char *s2){
  return !strcmp(s1, s2) && (strlen(s1) == strlen(s2));
}

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
    (*ret)[i] = calloc(FIELDSIZE, sizeof(char));

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

int check_legal_double(char *s, int row){
  char *testbufref, testbuf[FIELDSIZE];
  
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

int legal_amounts(Ledger *ledger){
  int i;

  if(ledger == NULL)
    return 1;

  for(i = 0; i < ledger->n; ++i)
    if(check_legal_double(ledger->text_content[0][i], i))
      return 1;

  return 0;
}
 
int is_space(char c){
  return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == 'v');
}

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

int contains_tabs(char *s){
  int i, n = strlen(s);
  for(i = 0; i < n; ++i)
    if(s[i] == '\t')
      return i;
  return 0;
}

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
  
  /* parse the data */
  for(; i < strlen(s); ++i){
    c = s[i];
      
    if(c== '\t'){
      if(field < FIELDSIZE){
        j = 0;
      }
      ++field; 
    } else if(c == '\n' || c == '\r'){
      if(field < FIELDSIZE){
        j = 0;
      }
      field = 0;
      ++row; 
    } else if(field < NFIELDS && j < FIELDSIZE - 1){
      ledger->text_content[field][row][j] = c;
      ++j;
    }
  } 
   
  return legal_amounts(ledger);
}

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
      if(field < FIELDSIZE){
        i = 0;
      }
      ++field; 
    } else if(c == '\n' || c == '\r'){
      if(field < FIELDSIZE){
        i= 0;
      }
      field = 0;
      ++row; 
    } else if(field < NFIELDS && i < FIELDSIZE - 1){
      ledger->text_content[field][row][i] = c;
      ++i; 
    }
  }
  
  rewind(fp);
  return legal_amounts(ledger);
}

void get_names(Ledger *ledger){
  int i, j;
  char **s = malloc(ledger->n * sizeof(char*));

  for(i = 0; i < ledger->n; ++i){
    s[i] = calloc(FIELDSIZE, sizeof(char));
    strcpy(s[i], ledger->text_content[2][i]);
  }
     
  unique(s, ledger->n, &ledger->credit, &ledger->ncredit);
    
  for(i = 0; i < ledger->n; ++i)
    strcpy(s[i], ledger->text_content[3][i]);
  
  unique(s, ledger->n, &ledger->bank, &ledger->nbank);
  
  ledger->npartition = calloc(ledger->nbank, sizeof(int*));
  ledger->partition = malloc(ledger->nbank * sizeof(char***));
        
  for(i = 0; i < ledger->nbank; ++i){
    for(j = 0; j < ledger->n; ++j){         
      strcpy(s[j], ledger->text_content[4][j]);
      if(!str_equal(ledger->bank[i], ledger->text_content[3][j]))
        strcpy(s[j], NIL);
    }
     
    unique(s, ledger->n, &(ledger->partition[i]), &(ledger->npartition[i]));
  }
  
  for(i = 0; i < ledger->n; ++i)
    free(s[i]);
  free(s);
}

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
    status = ledger->text_content[1][i];
    amount = atof(ledger->text_content[0][i]);

    k = -1;
    if(str_equal(status, CREDIT_NOTTHEREYET)){
      k = 0;
    } else if(str_equal(status, CREDIT_PENDING)){
      k = 1;
    } else if(str_equal(status, CREDIT_CLEARED)){
      k = 2;
    } 

    if(k != -1)
      for(j = 0; j < ledger->ncredit; ++j) 
        if(str_equal(ledger->text_content[2][i], ledger->credit[j])){
          ledger->credit_totals[j][k] += amount;
          break;
        }
      
    if(str_equal(status, CREDIT_NOTTHEREYET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) || 
       str_equal(status, NOTTHEREYET)){
      k = 0;
    } else if(str_equal(status, PENDING)){
      k = 1;
    } else {
      k = 2;
    }
    
    for(j = 0; j < ledger->nbank; ++j){
      if(str_equal(ledger->text_content[3][i], ledger->bank[j])){
        ledger->bank_totals[j][k] += amount;

        for(k = 0; k < ledger->npartition[j]; ++k){
          if(str_equal(ledger->text_content[4][i], ledger->partition[j][k])){
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
      ledger->credit_totals[j][3] += ledger->credit_totals[j][k];

  for(j = 0; j < ledger->nbank; ++j)
    for(k = 0; k < 3; ++k){
      ledger->bank_totals[j][3] += ledger->bank_totals[j][k];
    }  
}

Ledger *new_ledger(){
  Ledger *ledger = malloc(sizeof(Ledger));
  ledger->n = 1;
  ledger->filename = NULL;
  alloc_text_content(ledger);
  get_names(ledger);
  get_totals(ledger);   
  return ledger; 
}

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
 
void print_summary(Ledger *ledger, FILE *fp){
  int i, j, l0, l1, l2, any = 0, anyp = 0;
  double eps = 0.004;

  if(ledger == NULL || fp == NULL)
    return;

  fprintf(fp, "%s", KNRM);

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][0]) > eps);
    l1 = (abs(ledger->credit_totals[i][1]) > eps);
    l2 = (abs(ledger->credit_totals[i][2]) > eps);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credit[i]))
        fprintf(fp,"\nCredit account: %s\n\n", ledger->credit[i]);
      else
        fprintf(fp,"\nCredit account with no name:\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", ksgn(ledger->credit_totals[i][0]), 
                  ledger->credit_totals[i][0], KNRM); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", ksgn(ledger->credit_totals[i][1]), 
                  ledger->credit_totals[i][1], KNRM);
        fprintf(fp, "\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", ksgn(ledger->credit_totals[i][2]),
               ledger->credit_totals[i][2], KNRM);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  ksgn(ledger->credit_totals[i][1] + ledger->credit_totals[i][2]),
                  ledger->credit_totals[i][1] + ledger->credit_totals[i][2],
                  KNRM);
        fprintf(fp,"%s%30.2f%s  true balance\n", ksgn(ledger->credit_totals[i][3]),
                ledger->credit_totals[i][3], KNRM);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", ksgn(ledger->credit_totals[i][3]), 
                ledger->credit_totals[i][3], KNRM); 
        fprintf(fp,"                                All charges cleared.\n");
      }
    }
  }
          
  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][0]) > eps);
    l1 = (abs(ledger->bank_totals[i][1]) > eps);
    l2 = (abs(ledger->bank_totals[i][2]) > eps); 
  
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->bank[i]))
        fprintf(fp,"\nBank account: %s\n\n", ledger->bank[i]);
      else 
        fprintf(fp,"\nBank account with no name\n\n");
 
      if(l0 || l1){
        fprintf(fp,"          Delayed money:\n");
        if(l0)
          fprintf(fp,"%s%30.2f%s  not arrived\n", ksgn(ledger->bank_totals[i][0]),
                  ledger->bank_totals[i][0], KNRM); 
        if(l1)
          fprintf(fp,"%s%30.2f%s  pending\n", ksgn(ledger->bank_totals[i][1]), 
                  ledger->bank_totals[i][1], KNRM); 
        fprintf(fp,"\n          Balances:\n");
        fprintf(fp,"%s%30.2f%s  \"available\"\n", ksgn(ledger->bank_totals[i][2]),
                ledger->bank_totals[i][2], KNRM);
        if(l1 && l0)
          fprintf(fp,"%s%30.2f%s  pending balance\n", 
                  ksgn(ledger->bank_totals[i][1] + ledger->bank_totals[i][2]),
                  ledger->bank_totals[i][1] + ledger->bank_totals[i][2], KNRM);
        fprintf(fp,"%s%30.2f%s  true balance\n", ksgn(ledger->bank_totals[i][3]),
                ledger->bank_totals[i][3], KNRM);
      } else {
        fprintf(fp,"          Balances:\n");
        fprintf(fp,"%s%30.2f%s  true balance\n", ksgn(ledger->bank_totals[i][3]),
                ledger->bank_totals[i][3], KNRM);
        fprintf(fp,"                                All charges cleared.\n");
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > eps){
        if(strlen(ledger->partition[i][j])){
          if(!anyp){
            fprintf(fp,"\n          Partitions:\n");
            ++anyp;
          }
          fprintf(fp,"%s%30.2f%s  %s\n", ksgn(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], KNRM, ledger->partition[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][2]) > eps){
          if(!j) fprintf(fp, "\n");
          fprintf(fp,"%s%30.2f%s  unpartitioned\n", ksgn(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], KNRM);
        }
      } 
  }
  
  if(any)
    fprintf(fp,"\n");
}

char *print_summary_to_string(Ledger *ledger){
  int i, j, l0, l1, l2, any = 0, anyp = 0;
  double eps = 0.004;
  char *s;

  if(ledger == NULL)
    return NULL;
    
  s = calloc(ledger->n * NFIELDS * FIELDSIZE, sizeof(char));

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][0]) > eps);
    l1 = (abs(ledger->credit_totals[i][1]) > eps);
    l2 = (abs(ledger->credit_totals[i][2]) > eps);      
 
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->credit[i]))
        sprintf(s,"%s\nCredit account: %s\n\n", s, ledger->credit[i]);
      else
        sprintf(s,"%s\nCredit account with no name:\n\n", s);
 
      if(l0 || l1){
      
        sprintf(s,"%s          Delayed money:\n",s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, ksgn(ledger->credit_totals[i][0]), 
                  ledger->credit_totals[i][0], KNRM); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n", s, ksgn(ledger->credit_totals[i][1]), 
                  ledger->credit_totals[i][1], KNRM);

        sprintf(s, "%s\n          Balances:\n", s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, ksgn(ledger->credit_totals[i][2]),
               ledger->credit_totals[i][2], KNRM);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  ksgn(ledger->credit_totals[i][1] + ledger->credit_totals[i][2]),
                  ledger->credit_totals[i][1] + ledger->credit_totals[i][2],
                  KNRM);
        sprintf(s,"%s%s%30.2f%s  true balance\n",s, ksgn(ledger->credit_totals[i][3]),
                ledger->credit_totals[i][3], KNRM);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s, ksgn(ledger->credit_totals[i][3]), 
                ledger->credit_totals[i][3], KNRM); 
        sprintf(s,"%s                                All charges cleared.\n", s);
      }
    }
  }     
          
  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][0]) > eps);
    l1 = (abs(ledger->bank_totals[i][1]) > eps);
    l2 = (abs(ledger->bank_totals[i][2]) > eps); 
  
    if(l0 || l1 || l2){
      ++any;
      if(strlen(ledger->bank[i]))
        sprintf(s,"%s\nBank account: %s\n\n", s, ledger->bank[i]);
      else 
        sprintf(s,"%s\nBank account with no name\n\n", s);
 
      if(l0 || l1){
        sprintf(s,"%s          Delayed money:\n", s);
        if(l0)
          sprintf(s,"%s%s%30.2f%s  not arrived\n", s, ksgn(ledger->bank_totals[i][0]),
                  ledger->bank_totals[i][0], KNRM); 
        if(l1)
          sprintf(s,"%s%s%30.2f%s  pending\n",s, ksgn(ledger->bank_totals[i][1]), 
                  ledger->bank_totals[i][1], KNRM); 
        sprintf(s,"%s\n          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  \"available\"\n",s, ksgn(ledger->bank_totals[i][2]),
                ledger->bank_totals[i][2], KNRM);
        if(l1 && l0)
          sprintf(s,"%s%s%30.2f%s  pending balance\n", s,
                  ksgn(ledger->bank_totals[i][1] + ledger->bank_totals[i][2]),
                  ledger->bank_totals[i][1] + ledger->bank_totals[i][2], KNRM);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,ksgn(ledger->bank_totals[i][3]),
                ledger->bank_totals[i][3], KNRM);
      } else {
        sprintf(s,"%s          Balances:\n",s);
        sprintf(s,"%s%s%30.2f%s  true balance\n", s,ksgn(ledger->bank_totals[i][3]),
                ledger->bank_totals[i][3], KNRM);
        sprintf(s,"%s                                All charges cleared.\n",s);
      } 
    }

    anyp = 0;
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > eps){
        if(strlen(ledger->partition[i][j])){
          if(!anyp){
            sprintf(s,"%s\n          Partitions:\n",s);
            ++anyp;
          }
          sprintf(s,"%s%s%30.2f%s  %s\n",s, ksgn(ledger->partition_totals[i][j]), 
                  ledger->partition_totals[i][j], KNRM, ledger->partition[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][2]) > eps){
          if(!j) sprintf(s, "%s\n",s);
          sprintf(s,"%s%s%30.2f%s  unpartitioned\n",s, ksgn(ledger->partition_totals[i][j]),
                  ledger->partition_totals[i][j], KNRM);
        }
      } 
  }
  
  if(any)
    sprintf(s,"%s\n",s);
    
  return s;
}



int check_legal_double_modify(char *s){
  char *testbufref, testbuf[FIELDSIZE];
  
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

void modify(Ledger *ledger, int row, int col, char *next){

  char next_local[FIELDSIZE];
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

void rename_credit(Ledger *ledger, char *from, char *to){
  int i;

  if(ledger == NULL)
    return;

  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[2][i], from))
      strcpy(ledger->text_content[2][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}

void rename_bank(Ledger *ledger, char *from, char *to){
  int i;
  
  if(ledger == NULL)
    return;
  
  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[3][i], from))
      strcpy(ledger->text_content[3][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}

void rename_partition(Ledger *ledger, char *bank, char *from, char *to){
  int i;
  
  if(ledger == NULL)
    return;
  
  for(i = 0; i < ledger->n; ++i)
    if(str_equal(ledger->text_content[3][i], bank) && 
       str_equal(ledger->text_content[4][i], from))
      strcpy(ledger->text_content[4][i], to);
  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger);   
}

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
      x[i][j] = calloc(FIELDSIZE, sizeof(char));
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

void remove_row(Ledger *ledger, int row){
  int i, j, recalculate;
  float eps = 0.004;
  
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

  recalculate = (abs(atof(ledger->text_content[0][row])) > eps);

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

void trim_ledger(Ledger *ledger){
  int i;
  float eps = 0.004;

  if(ledger == NULL)
    return;

  for(i = (ledger->n - 1); i >= 0; --i)
    if(abs(atof(ledger->text_content[0][i])) < eps)
      remove_row(ledger, i);
}
 
Ledger *get_ledger_from_string(char *s){
  Ledger *ledger = calloc(1, sizeof(Ledger));
  if(get_text_content_from_string(ledger, s)){
    free_ledger(ledger);
    return NULL;
  }
  trim_ledger(ledger);
  get_names(ledger);
  get_totals(ledger);
  return ledger;
} 
 
void condense(Ledger **ledger){
  int i, j, k, new_n, row = 0;
  double eps = 0.004, **local_partition_totals;
  char status[FIELDSIZE], amount[FIELDSIZE];
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
    strcpy(status, (*ledger)->text_content[1][i]);
    strcpy(amount, (*ledger)->text_content[0][i]);
  
    if(str_equal(status, CREDIT_NOTTHEREYET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOTTHEREYET) || 
       str_equal(status, PENDING) ||
       str_equal(status, LOCKED)){ 

      for(j = 0; j < (*ledger)->nbank; ++j)
        if(str_equal((*ledger)->text_content[3][i], (*ledger)->bank[j])){
         for(k = 0; k < (*ledger)->npartition[j]; ++k){
            if(str_equal((*ledger)->text_content[4][i], (*ledger)->partition[j][k])){
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
    new_n += (strlen((*ledger)->text_content[1][i]) > 0);

  for(i = 0; i < (*ledger)->nbank; ++i)
    new_n += (*ledger)->npartition[i];

  newledger->n = new_n;
  alloc_text_content(newledger);  
  
  for(i = 0; i < (*ledger)->n; ++i){
    strcpy(status, (*ledger)->text_content[1][i]);
    strcpy(amount, (*ledger)->text_content[0][i]);
  
    if(str_equal(status, CREDIT_NOTTHEREYET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOTTHEREYET) || 
       str_equal(status, PENDING) || 
       str_equal(status, LOCKED)){ 
      
      if(abs(atof(amount)) > eps){
        for(j = 0; j < NFIELDS; ++j)
          strcpy(newledger->text_content[j][row], (*ledger)->text_content[j][i]);
        ++row;
      }
    }
  } 
   
  for(i = 0; i < (*ledger)->nbank; ++i)
    for(j = 0; j < (*ledger)->npartition[i]; ++j)
      if(abs(local_partition_totals[i][j]) > eps){
        sprintf(amount, "%0.2f", local_partition_totals[i][j]);
        strcpy(newledger->text_content[0][row], amount);
        strcpy(newledger->text_content[3][row], (*ledger)->bank[i]);
        strcpy(newledger->text_content[4][row], (*ledger)->partition[i][j]);
        strcpy(newledger->text_content[5][row], "condensed");
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
    fprintf(fp, "    %0.2f not arrived\n", ledger->credit_totals[i][0]);
    fprintf(fp, "    %0.2f pending\n", ledger->credit_totals[i][1]);
    fprintf(fp, "    %0.2f online balance\n", ledger->credit_totals[i][2]);
    fprintf(fp, "    %0.2f total\n", ledger->credit_totals[i][3]);
  }
  
  fprintf(fp, "\n%d bank accounts:\n", ledger->nbank);
  for(i = 0; i < ledger->nbank; ++i){
    fprintf(fp, "\n  %s bank account:\n", ledger->bank[i]);
    fprintf(fp, "    %0.2f\tnot arrived\n", ledger->bank_totals[i][0]);
    fprintf(fp, "    %0.2f\tpending\n", ledger->bank_totals[i][1]);
    fprintf(fp, "    %0.2f\tonline balance\n", ledger->bank_totals[i][2]);
    fprintf(fp, "    %0.2f\ttotal\n\n", ledger->bank_totals[i][3]);
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
 
char *print_ledger_to_string(Ledger *ledger){
  char *s, entry[FIELDSIZE], 
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
    strcat(s, ledger->text_content[0][j]);
    
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
 
int summarize_file_to_stream(const char* filename, FILE *fp){
  Ledger *ledger = get_ledger_from_filename(filename);
  int ind = (ledger == NULL);
  
  if(ind)
    return 1;

  print_summary(ledger, fp);
  
  free_ledger(ledger);
  return 0;
}

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

int main(int argc, char **argv){ /*
  return standalone(argc, argv) ? EXIT_FAILURE : EXIT_SUCCESS; */
  
  Ledger *ledger = get_ledger_from_filename(argv[1]); 
  char *s = print_summary_to_string(ledger);
  
  
  
  
  FILE *fp = fopen("ddd.txt", "w");
  if(s != NULL)
    fprintf(fp, "%s", s);
  fclose(fp);
  

  
  fp = fopen("ddd.txt", "w");
    print_summary(ledger, fp);
   fclose(fp);
  
  if(s != NULL)
    free(s); 
    
   free_ledger(ledger);
        return 0;
}
