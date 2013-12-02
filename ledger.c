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

#define NFIELDS 6
#define FIELDSIZE 128
#define LINESIZE 512
#define FILENAMESIZE 256

typedef struct {
  char *filename, **credit, **bank, ***partition, ***text_content;
  int n, ncredit, nbank, *npartition;
  double  **credit_totals, **bank_totals, **partition_totals;
} Ledger;

void alloc_text_content(Ledger *ledger){
  int i, j;
  ledger->text_content = malloc(NFIELDS * sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->text_content[i] = malloc(ledger->n * sizeof(char*));
    for(j = 0; j < ledger->n; ++j)
      ledger->text_content[i][j] = calloc(FIELDSIZE, sizeof(char));
  }
}

int qcmp(const void *a, const void *b){ 
  const char **ia = (const char **) a;
  const char **ib = (const char **) b;
  return strcmp(*ia, *ib); 
} 

int mycmp(const char *s1, const char *s2){
  int ret;
  ret = strcmp(s1, s2) || (strlen(s1) != strlen(s2));
  return ret;
}

void unique(char **s, int n, char ***ret, int *nunique){
  int i = 0, j, k;

  qsort(s, n, sizeof(char*), qcmp);

  *nunique = 0;  
  if(s[0][0] != '\0')
    ++(*nunique);

  for(j = 1; j < n; ++j){
    if(mycmp(s[i], s[j])){
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
    if(mycmp(s[i], s[j])){
      if(s[j][0] != '\0'){
        i = j;
        strcpy((*ret)[k], s[j]);
        ++k;
      }
    }  
}

void emergency_free(Ledger *ledger, FILE *fp){
  int i, j;
  
  fclose(fp);
  
  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < ledger->n; ++j)
      free(ledger->text_content[i][j]);
    free(ledger->text_content[i]);
  }
  free(ledger->text_content);  
  free(ledger->filename);
  free(ledger);
}

int check_legal_float(char *s, int row){
  char *testbufref, testbuf[FIELDSIZE];
  
  errno = 0;
  strcpy(testbuf, s);
    testbufref = testbuf;
    strtod(testbuf, &testbufref); 
    if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf)){
      fprintf(stderr, "Error: bad number %s at row %d column 2.\n", 
              s, row + 1);
      fprintf(stderr, "Fix your ledger file.\n");
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
    memmove(s, start, end-start+1);      

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
  FILE *fp = fopen(ledger->filename, "r");
  
  ledger->n = 0;
  while(fgets(line, LINESIZE, fp))
    ++ledger->n;
    
  rewind(fp);
  alloc_text_content(ledger);
  
  row = 0;
  field = 0;

  while(fgets(line, LINESIZE, fp)){
    str = line;
    for(field = 0; field < NFIELDS; ++field){
      token = local_strsep(&str, "\f\n\r\t\v");
      if(token == NULL)
        continue;
      
      if(field == 1) 
        if(check_legal_float(token, row)){
          emergency_free(ledger, fp);
          return 1;
        }
    
      strstrip(token);
      strcpy(ledger->text_content[field][row], token);
    }
    ++row;
  }
  
  fclose(fp);
  return 0;
}

void get_names(Ledger *ledger){
  int i, j;
  char nil[] = "\0", **s = malloc(ledger->n * sizeof(char*));

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
      if(mycmp(ledger->bank[i], ledger->text_content[3][j]))
        strcpy(s[j], nil);
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
    ledger->credit_totals[i] = calloc(3, sizeof(double));
      
  ledger->bank_totals = calloc(ledger->nbank, sizeof(double*));  
  for(i = 0; i < ledger->nbank; ++i)
    ledger->bank_totals[i] = calloc(3, sizeof(double));
  
  ledger->partition_totals = malloc(ledger->nbank * sizeof(double*));
  for(i = 0; i < ledger->nbank; ++i)
    ledger->partition_totals[i] = calloc(ledger->npartition[i], sizeof(double));
    
  for(i = 0; i < ledger->n; ++i){
    status = ledger->text_content[0][i];
    amount = atof(ledger->text_content[1][i]);

    k = -1;
    if(!mycmp(status, CREDIT_NOTTHEREYET)){
      k = 0;
    } else if(!mycmp(status, CREDIT_PENDING)){
      k = 1;
    } else if(!mycmp(status, CREDIT_CLEARED)){
      k = 2;
    } 

    if(k != -1)
      for(j = 0; j < ledger->ncredit; ++j) 
        if(!mycmp(ledger->text_content[2][i], ledger->credit[j])){
          ledger->credit_totals[j][k] += amount;
          break;
        }
      
    if(!mycmp(status, CREDIT_NOTTHEREYET) || 
       !mycmp(status, CREDIT_PENDING) || 
       !mycmp(status, CREDIT_CLEARED) || 
       !mycmp(status, NOTTHEREYET)){
      k = 0;
    } else if(!mycmp(status, PENDING)){
      k = 1;
    } else {
      k = 2;
    }
    
    for(j = 0; j < ledger->nbank; ++j){
      if(!mycmp(ledger->text_content[3][i], ledger->bank[j])){
        ledger->bank_totals[j][k] += amount;

       for(k = 0; k < ledger->npartition[j]; ++k){
          if(!mycmp(ledger->text_content[4][i], ledger->partition[j][k])){
            ledger->partition_totals[j][k] += amount;
            break;
          }
        } 

        break;
      }
    }
  }  
}

Ledger *make_ledger(const char* filename){
  Ledger *ledger = malloc(sizeof(Ledger));
  ledger->filename = malloc(FILENAMESIZE * sizeof(char));
  strcpy(ledger->filename, filename);
  if(get_text_content(ledger))
    return NULL;
  get_names(ledger);
  get_totals(ledger); 
  return ledger;
}

void print_summary(Ledger *ledger){
  int i, j, k, l0, l1, l2;
  double eps = 0.004, leftover;

  for(i = 0; i < ledger->ncredit; ++i){
    l0 = (abs(ledger->credit_totals[i][0]) > eps);
    l1 = (abs(ledger->credit_totals[i][1]) > eps);
    l2 = (abs(ledger->credit_totals[i][2]) > eps);      
  
    if(l0 || l1 || l2){
      printf("\n----- Credit card: %s -----\n\n", ledger->credit[i]);
      if(l2)
        printf("%0.2f\tcharged\n", ledger->credit_totals[i][2]);
      if(l1)
        printf("%0.2f\tpending\n", ledger->credit_totals[i][1]); 
      if(l0)
        printf("%0.2f\tnot arrived\n", ledger->credit_totals[i][0]); 
      if((l0 && l1) || (l1 && l2) || (l0 && l2))
        printf("%0.2f\ttotal\n", ledger->credit_totals[i][0] 
               + ledger->credit_totals[i][1] 
               + ledger->credit_totals[i][2]);
    }
  }
  
  for(i = 0; i < ledger->nbank; ++i){
    l0 = (abs(ledger->bank_totals[i][0]) > eps);
    l1 = (abs(ledger->bank_totals[i][1]) > eps);
    l2 = (abs(ledger->bank_totals[i][2]) > eps); 
  
    if(l0 || l1 || l2)
      printf("\n----- Bank account: %s -----\n\n", ledger->bank[i]);
    if(!l0 && !l1 && l2){
      printf("%0.2f\ttrue balance\n", ledger->bank_totals[i][0] 
                                    + ledger->bank_totals[i][1] 
                                    + ledger->bank_totals[i][2]);
      printf("\tAll charges cleared.\n");
    } else {
       if(l2)
         printf("%0.2f\tcleared\n", ledger->bank_totals[i][2]);
       if(l1 && l2)
         printf("%0.2f\tcleared or pending\n", 
                ledger->bank_totals[i][1] + ledger->bank_totals[i][2]); 
       if(l0 && (l1 || l2))
         printf("%0.2f\ttrue balance\n", ledger->bank_totals[i][0] 
                                       + ledger->bank_totals[i][1] 
                                       + ledger->bank_totals[i][2]);
    }

    leftover = ledger->bank_totals[i][0] 
             + ledger->bank_totals[i][1] 
             + ledger->bank_totals[i][2];
    
    k = 0;
    for(j = 0; j < ledger->npartition[i]; ++j){
      if(abs(ledger->partition_totals[i][j]) > eps){
        if(!k){
          printf("\n");
          ++k;
        }
        printf("%0.2f\t%s partition\n", ledger->partition_totals[i][j], 
                                        ledger->partition[i][j]);
        leftover -= ledger->partition_totals[i][j];
      }
    }
    
    if(ledger->npartition[i] && (abs(leftover) > eps))
      printf("%0.2f\tunpartitioned\n", leftover);  
  }
  printf("\n");
}

void free_ledger(Ledger *ledger){
  int i, j;

  for(i = 0; i < ledger->ncredit; ++i){
    free(ledger->credit[i]);
    free(ledger->credit_totals[i]);
  }
  free(ledger->credit);
  free(ledger->credit_totals);

  for(i = 0; i < ledger->nbank; ++i){
    free(ledger->bank[i]);
    free(ledger->bank_totals[i]);
    for(j = 0; j < ledger->npartition[i]; ++j)
      free(ledger->partition[i][j]);
    free(ledger->partition[i]);
    free(ledger->partition_totals[i]);
  } 
  free(ledger->bank);
  free(ledger->bank_totals);
  free(ledger->partition);
  free(ledger->partition_totals); 
  
  for(i = 0; i < NFIELDS; ++i){
    for(j = 0; j < ledger->n; ++j)
      free(ledger->text_content[i][j]);
    free(ledger->text_content[i]);
  }
  free(ledger->text_content);  
  free(ledger->npartition);
  free(ledger->filename);
  free(ledger);
}

int summarize(const char* filename){
  Ledger *ledger = make_ledger(filename);
  if(ledger == NULL){
    printf("Failed to read ledger.\n");
    return 1;
  }
  print_summary(ledger);
  free_ledger(ledger);
  return 0;
}

int condense(const char* infile, const char *outfile){
  int i, j, k;
  double eps = 0.004, leftover;
  FILE *fp;
  Ledger *ledger = make_ledger(infile);
  
  if(ledger == NULL){
    printf("Failed to read ledger.\n");
    return 1;
  }  
  
  fp = fopen(outfile, "w");
  
  for(i = 0; i < ledger->n; ++i){
    if(!mycmp(ledger->text_content[0][i], CREDIT_NOTTHEREYET) || 
       !mycmp(ledger->text_content[0][i], CREDIT_PENDING) || 
       !mycmp(ledger->text_content[0][i], CREDIT_CLEARED) ||
       !mycmp(ledger->text_content[0][i], NOTTHEREYET) || 
       !mycmp(ledger->text_content[0][i], PENDING)){
      fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\n", ledger->text_content[0][i],
              ledger->text_content[1][i], ledger->text_content[2][i],
              ledger->text_content[3][i], ledger->text_content[4][i],
              ledger->text_content[5][i]);

      for(j = 0; j < ledger->nbank; ++j)
        if(!mycmp(ledger->text_content[3][i], ledger->bank[j])){
          for(k = 0; k < ledger->npartition[j]; ++k)
            if(!mycmp(ledger->text_content[4][i], ledger->partition[j][k]))
              ledger->partition_totals[j][k] -= atof(ledger->text_content[1][i]);
       }
    }
  } 

  for(i = 0; i < ledger->nbank; ++i){
    leftover = ledger->bank_totals[i][2];
    k = 0;
    
    for(j = 0; j < ledger->npartition[i]; ++j){
      if(abs(ledger->partition_totals[i][j]) > eps){
        fprintf(fp, "\t%0.2f\t\t%s\t%s\tcondensed\n", ledger->partition_totals[i][j], 
                ledger->bank[i], ledger->partition[i][j]); 
                
        if(!k){
          ++k;
        }
        leftover -= ledger->partition_totals[i][j];
      }
    }
    
    if(abs(leftover) > eps)
      fprintf(fp, "\t%0.2f\t\t%s\t\tcondensed\n", leftover, ledger->bank[i]);
  }
    
  fclose(fp);
  free_ledger(ledger);
  return 0;
}

void usage(){
  printf("\nUsage: to summarize the ledger,\n$ ./ledger [LEDGER_FILE]\n");
  printf("\nTo condense the ledger,\n$ ./ledger [INTPUT_LEDGER_FILE] [OUTTPUT_LEDGER_FILE]\n");
  printf("\nSee README.txt for details.\n");
}

int standalone(int argc, char **argv){
  FILE *fp;
  if(argc == 2 || argc == 3){
    fp = fopen(argv[1], "r");
    if(fp == NULL){
      fprintf(stderr, "Error: cannot open input file, %s.\nPossible reason: file does not exist.\n", argv[1]);
      return 1;
    } 
    fclose(fp);
  }
  
  if(argc == 2){
    if(summarize(argv[1])){
      printf("Exiting due to failure.\n");
      return 1;
    }
  } else if(argc == 3){
   
    if(condense(argv[1], argv[2])){
      printf("Exiting due to failure.\n");
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
