/*
 @author Will Landau
 @email will.landau@gmail.com
 @web http://will-landau.com
 @date December 1, 2013
 @license GPL 3.0
 @about Personal accounting software. More documentation to come. 
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

#define NIL "\0"
#define NFIELDS 6
#define FIELDSIZE 128
#define LINESIZE 4096
#define FILENAMESIZE 256

typedef struct {
  char *filename, **credit, **bank, ***partition, ***text_content;
  int n, ncredit, nbank, *npartition;
  double **credit_totals, **bank_totals, **partition_totals;
  FILE *fp;
} Ledger;

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

  if(ledger->fp != NULL)
    fclose(ledger->fp);

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

void alloc_text_content(Ledger *ledger){
  int i, j;
  ledger->text_content = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->text_content[i] = malloc(ledger->n * sizeof(char*));
    for(j = 0; j < ledger->n; ++j)
      ledger->text_content[i][j] = calloc(FIELDSIZE, sizeof(char));
  }
}

int badfile(const char *filename){
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

int check_legal_double_modify(char *s){
  char *testbufref, testbuf[FIELDSIZE];
  
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

/* The function local_strsep() (below) was originally strsep(), and its
 * copyright information is below.
 *
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

char *local_strsep(char **stringp, const char *delim){
  char *s;
  const char *spanp;
  int c, sc;
  char *tok;

  if ((s = *stringp) == NULL)
    return (NULL);

  for (tok = s;;){
    c = *s++;
    spanp = delim;
    do {
      if ((sc = *spanp++) == c){
        if (c == 0)
          s = NULL;
        else
          s[-1] = 0;
        *stringp = s;
        return (tok);
      }
    } while (sc != 0);
  }
}

int get_text_content(Ledger *ledger){
  int row, field; 
  char line[LINESIZE], *str, *token;
  
  ledger->n = 0;
  while(fgets(line, LINESIZE, ledger->fp))
    ++ledger->n;
  
  if(!ledger->n){
    fprintf(stderr, "Ledger file is empty.\n");
    free_ledger(ledger);
    return 1;
  }
    
  rewind(ledger->fp);
  alloc_text_content(ledger);
  
  row = 0;
  field = 0;

  while(fgets(line, LINESIZE, ledger->fp)){
    str = line;
    for(field = 0; field < NFIELDS; ++field){
      token = local_strsep(&str, "\f\n\r\t\v");
      if(token == NULL)
        continue;
      
      if(field == 0) 
        if(check_legal_double(token, row)){
          free_ledger(ledger);
          return 1;
        }
    
      strstrip(token);
      strcpy(ledger->text_content[field][row], token);
    }
    ++row;
  }
  
  rewind(ledger->fp);
  return 0;
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


Ledger *get_ledger_from_stream(FILE *fp){
  Ledger *ledger = calloc(1, sizeof(Ledger));
  ledger->fp = fp;
  if(get_text_content(ledger))
    return NULL;
  get_names(ledger);
  get_totals(ledger); 
  return ledger;
}

Ledger *get_ledger_from_filename(const char* filename){
  FILE *fp;
  Ledger *ledger = NULL;
  
  if(badfile(filename))
    return NULL;
  
  fp = fopen(filename, "r");
  ledger = get_ledger_from_stream(fp);
  
  if(ledger == NULL)
    return NULL;
    
  ledger->filename = malloc(FILENAMESIZE * sizeof(char));
  strcpy(ledger->filename, filename);
  
  return ledger;
}

void print_summary(Ledger *ledger){
  int i, j, l0, l1, l2;
  double eps = 0.004;

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][0]) > eps);
    l1 = (abs(ledger->credit_totals[i][1]) > eps);
    l2 = (abs(ledger->credit_totals[i][2]) > eps);      
 
    if(l0 || l1 || l2){
      printf("\n----- Credit account: %s -----\n\n", ledger->credit[i]);
 
      if(l0 || l1){
        if(l0)
          printf("%0.2f\tnot arrived\n", ledger->credit_totals[i][0]); 
        if(l1)
          printf("%0.2f\tpending\n", ledger->credit_totals[i][1]);
        printf("\n%0.2f\tonline balance\n", ledger->credit_totals[i][2]);
        if(l1 && l0)
          printf("%0.2f\tpending balance\n", ledger->credit_totals[i][1] 
                                           + ledger->credit_totals[i][2]);
        printf("%0.2f\ttrue balance\n", ledger->credit_totals[i][3]);
      } else {
        printf("%0.2f\ttrue balance\n", ledger->credit_totals[i][3]); 
        printf("\tAll charges cleared.\n");
      }
    }
  }

  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][0]) > eps);
    l1 = (abs(ledger->bank_totals[i][1]) > eps);
    l2 = (abs(ledger->bank_totals[i][2]) > eps); 
  
    if(l0 || l1 || l2){
      printf("\n----- Bank account: %s -----\n\n", ledger->bank[i]);
 
      if(l0 || l1){
        if(l0)
          printf("%0.2f\tnot arrived\n", ledger->bank_totals[i][0]); 
        if(l1)
          printf("%0.2f\tpending\n", ledger->bank_totals[i][1]); 
        printf("\n%0.2f\tonline balance\n", ledger->bank_totals[i][2]);
        if(l1 && l0)
          printf("%0.2f\tpending balance\n", ledger->bank_totals[i][1] 
                                           + ledger->bank_totals[i][2]);
        printf("%0.2f\ttrue balance\n", ledger->bank_totals[i][3]);
      } else {
        printf("%0.2f\ttrue balance\n", ledger->bank_totals[i][3]);
        printf("\tAll charges cleared.\n");
      } 
    }

    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > eps){
        if(strlen(ledger->partition[i][j])){
          if(!j) printf("\n");
          printf("%0.2f\t%s partition\n", ledger->partition_totals[i][j], 
                                          ledger->partition[i][j]);
        }
        else if(abs(ledger->partition_totals[i][j] - ledger->bank_totals[i][2]) > eps){
          if(!j) printf("\n");
          printf("%0.2f\tunpartitioned\n", ledger->partition_totals[i][j]);
        }
      } 
      
    if(i == (ledger->nbank - 1))
      printf("\n");
  }
}

void modify(Ledger *ledger, int row, int col, char *next){

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
      
  strcpy(ledger->text_content[col][row], next);

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
}
/*
void insert_in_array(char ***a, int at, int *n){
  int i;
  char **tmp, **b;

  if(a == NULL)
    return;
  
  if(at < 0 || at >= *n){
    fprintf(stderr, "Error: bad row index.\n");
    return;
  }
 
  b = malloc((*n + 1) * sizeof(char*));
 
  for(i = 0; i < (*n + 1); ++i)
    b[i] = malloc(FIELDSIZE * sizeof(char));
    
  for(i = 0; i < at; ++i)
    strcpy(b[i], (*a)[i]);
  
  strcpy(b[i], NIL); 
  
  printf("--%lu-%lu-\n", strlen("\0"), strlen(""));
  
  for(i = at + 1; i < *n + 1; ++i)
    strcpy(b[i], (*a)[i - 1]);

   
  tmp = *a;
  *a = b;
  
  for(i = 0; i < *n; ++i)
    free(tmp[i]);
  free(tmp);
  ++(*n); 
}

void remove_from_array(char **a, int at, int *n){
  int i;
  
  if(a == NULL)
    return;
  
  if(at < 0 || at >= *n){
    fprintf(stderr, "Error: bad row index.\n");
    return;
  }
  
  for(i = at; i < (*n - 1); ++i)
    strcpy(a[i], a[i + 1]);
  
  free(a[*n - 1]);
  --(*n); 
}
*/

void insert_row(Ledger *ledger, int row){

  if(ledger == NULL)
    return;
    
  if(row < 0 || row > ledger->n){
    printf("Error: illegal row index in modify().\n");
    return;
  }
  


  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
}

void remove_row(Ledger *ledger, int row){
  int i, j;
  
  if(ledger == NULL)
    return;
  
  if(row < 0 || row >= ledger->n){
    printf("Error: illegal row index in modify().\n");
    return;
  }
  
  if(ledger->n < 1){
    printf("Error: data already too small.\n");
    return;  
  }

  if(ledger->n == 1){
    for(i = 0; i < NFIELDS; ++i)
      strcpy(ledger->text_content[i][0], NIL);
    return;
  }
  
  for(i = 0; i < NFIELDS; ++i){
    for(j = row; j < (ledger->n - 1); ++j)
      strcpy(ledger->text_content[i][j], ledger->text_content[i][j + 1]);
    free(ledger->text_content[i][ledger->n - 1]);
  }
  
  --(ledger->n);

  free_for_retotal(ledger);
  get_names(ledger);
  get_totals(ledger); 
}

Ledger *condense(Ledger *ledger){
  int i, j, k, new_n, row = 0;
  double eps = 0.004, **local_partition_totals;
  char status[FIELDSIZE], amount[FIELDSIZE];
  Ledger *newledger;
  
  if(ledger == NULL)
    return NULL;

  local_partition_totals = malloc(ledger->nbank * sizeof(double*));
  for(i = 0; i < ledger->nbank; ++i){
    local_partition_totals[i] = calloc(ledger->npartition[i], sizeof(double));  
    for(j = 0; j < ledger->npartition[i]; ++j)
      local_partition_totals[i][j] = ledger->partition_totals[i][j];
  }

  for(i = 0; i < ledger->n; ++i){
    strcpy(status, ledger->text_content[1][i]);
    strcpy(amount, ledger->text_content[0][i]);
  
    if(str_equal(status, CREDIT_NOTTHEREYET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOTTHEREYET) || 
       str_equal(status, PENDING)){ 

      for(j = 0; j < ledger->nbank; ++j)
        if(str_equal(ledger->text_content[3][i], ledger->bank[j])){
         for(k = 0; k < ledger->npartition[j]; ++k){
            if(str_equal(ledger->text_content[4][i], ledger->partition[j][k])){
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
  newledger->fp = NULL;
  
  new_n = 0;
  for(i = 0; i < ledger->n; ++i)
    new_n += (strlen(ledger->text_content[1][i]) > 0);

  for(i = 0; i < ledger->nbank; ++i)
    new_n += ledger->npartition[i];

  newledger->n = new_n;
  alloc_text_content(newledger);  
  
  for(i = 0; i < ledger->n; ++i){
    strcpy(status, ledger->text_content[1][i]);
    strcpy(amount, ledger->text_content[0][i]);
  
    if(str_equal(status, CREDIT_NOTTHEREYET) || 
       str_equal(status, CREDIT_PENDING) || 
       str_equal(status, CREDIT_CLEARED) ||
       str_equal(status, NOTTHEREYET) || 
       str_equal(status, PENDING)){ 
       
      for(j = 0; j < NFIELDS; ++j)
        strcpy(newledger->text_content[j][row], ledger->text_content[j][row]);
      ++row;
    }
  } 
   
  for(i = 0; i < ledger->nbank; ++i)
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(local_partition_totals[i][j]) > eps){
        sprintf(amount, "%0.2f", local_partition_totals[i][j]);
        strcpy(newledger->text_content[0][row], amount);
        strcpy(newledger->text_content[3][row], ledger->bank[i]);
        strcpy(newledger->text_content[4][row], ledger->partition[i][j]);
        strcpy(newledger->text_content[5][row], "condensed");
        ++row;
      }

  for(i = 0; i < ledger->nbank; ++i)
    free(local_partition_totals[i]);  
  free(local_partition_totals); 

  get_names(newledger);
  get_totals(newledger); 

  return newledger;
}

void print_ledger(Ledger *ledger, FILE *fp){
  int i, j;
  double amount;
  
  if(ledger == NULL || fp == NULL)
    return;
  
  for(i = 0; i < ledger->n; ++i){
    amount = atof(ledger->text_content[0][i]);
    fprintf(fp, "%0.2f", amount);
    for(j = 1; j < NFIELDS; ++j)
      fprintf(fp, "\t%s", ledger->text_content[j][i]);
    fprintf(fp, "\n");
  }
}

void print_ledger_verbose(Ledger *ledger, FILE *fp){
  int i, j;

  if(ledger == NULL || fp == NULL)
    return;
    
  if(ledger->filename != NULL)
    fprintf(fp, "filename = %s.\n", ledger->filename);
  
  if(ledger->fp == NULL)
    fprintf(fp, "File pointer is null.\n");
  else
    fprintf(fp, "File pointer is allocated.\n");
   
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
  print_ledger(ledger, fp);
}

int condense_and_print(const char* infile, const char *outfile){
  FILE *fp;
  Ledger *ledger, *newledger;
  
  if(badfile(infile))
    return 1;
  
  ledger = get_ledger_from_filename(infile);
  if(ledger == NULL){
    printf("Failed to read ledger.\n");
    return 1;
  }  
  
  newledger = condense(ledger);
  
  if(!badoutputfile(outfile)){
    fp = fopen(outfile, "w");
    print_ledger(newledger, fp);
    fclose(fp);
  }
  
  free_ledger(ledger);
  free_ledger(newledger);
  return 0;
}




int summarize(const char* filename){
  Ledger *ledger = get_ledger_from_filename(filename);
  int ind = (ledger == NULL);
  
  if(ind)
    return 1;

  print_summary(ledger);
  
  free_ledger(ledger);
  return 0;
}

void usage(){
  printf("\nUsage: to summarize the ledger,\n$ ./ledger [LEDGER_FILE]\n");
  printf("\nTo condense the ledger,\n$ ./ledger [INTPUT_LEDGER_FILE] [OUTTPUT_LEDGER_FILE]\n");
  printf("\nSee README.txt for details.\n");
}

int standalone(int argc, char **argv){
  if(argc == 2){
    if(summarize(argv[1])){
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
  return standalone(argc, argv) ? EXIT_FAILURE : EXIT_SUCCESS;
  */
  
  Ledger *ledger = get_ledger_from_filename(argv[1]);
  
  if(ledger != NULL){
    print_ledger_verbose(ledger, stdout);
  
    remove_row(ledger, 7);
    remove_row(ledger, 6);
    
    printf("\n\n===========\n\n");
    
        print_ledger_verbose(ledger, stdout);
    free_ledger(ledger);
  }
  
  
  return 0;
}
