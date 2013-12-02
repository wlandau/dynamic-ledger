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
#define FILENAMESIZE 128

typedef struct {
  char *filename, **credit, **bank, ***partition, ***text_content;
  int n, ncredit, nbank, *npartition;
  double  **credit_totals, **bank_totals, **partition_totals;
} Ledger;

void alloc_text_content(Ledger *ledger){
  int i, j;
  ledger->text_content = calloc(NFIELDS, sizeof(char**));
  for(i = 0; i < NFIELDS; ++i){
    ledger->text_content[i] = calloc(ledger->n, sizeof(char*));
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

int get_text_content(Ledger *ledger){
  int i = 0, field = 0, ntabs = 0, nlines = 0;
  char c = '0', *entry, *testbufref, testbuf[FIELDSIZE];
  FILE *fp = fopen(ledger->filename, "r");
  
  ledger->n = 0;
  while(!feof(fp)){
    c = fgetc(fp);
    if(c == '\n' || c == EOF)
      ++ledger->n;
  }
  rewind(fp);

  entry = malloc(FIELDSIZE * sizeof(char));
  sprintf(entry, "%s", "");
  alloc_text_content(ledger);

  while(!feof(fp)){
    c = fgetc(fp);
    if(c == '\n' || c == '\t' || c == EOF){
      strcpy(ledger->text_content[field][i], entry);
      
      ++field;
      if(c == '\t'){
        ++ntabs;
        if(ntabs >= NFIELDS){
          sprintf(entry, "Error: wrong number of tab delimiters near line %d. \
                          \nFix your ledger file.\n", nlines);
          return 1;
        }
        
      } else if(c == '\n' && ntabs > 0){
        ++i;
        ++nlines;
        
        if(ntabs != NFIELDS - 1 && ntabs != 0){
          sprintf(entry, "Error: wrong number of tab delimiters near line %d. \
                          \nFix your ledger file.\n", nlines);
          return 1;
        }
        
        ntabs = 0;
        field = 0;
      }
      
      sprintf(entry, "%s", ""); 
    } else{
      sprintf(entry, "%s%c", entry, c);
    }
  }
  
  ledger->n = nlines;
  
  for(i = 1; i < ledger->n; ++i){
    errno = 0;
    strcpy(testbuf, ledger->text_content[1][i]);
    testbufref = testbuf;
    strtod(testbuf, &testbufref); 
    if((errno || testbuf == testbufref || *testbufref != 0) && strlen(testbuf)){
      sprintf(entry, "Error: bad number in \"amount\" field near line %d. \
                      \nFix your ledger file.\n", i);
      return 1;   
    }
  }
  
  free(entry);
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
    
  for(i = 1; i < ledger->n; ++i){
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
    printf("\nFailed to read ledger.\n");
    return 1;
  }
  print_summary(ledger);
  free_ledger(ledger);
  return 0;
}

int condense(const char* infile, const char *outfile){
  int i, j, k;
  double eps = 0.004;
  FILE *fp;
  Ledger *ledger = make_ledger(infile);
  
  if(ledger == NULL){
    printf("\nFailed to read ledger.\n");
    return 1;
  }  
  
  fp = fopen(outfile, "w");
  
  fprintf(fp, "status\tamount\tcredit\tbank\tpartition\tmemo\n");
  for(i = 1; i < ledger->n; ++i){
    if(!mycmp(ledger->text_content[0][i], CREDIT_NOTTHEREYET) || 
       !mycmp(ledger->text_content[0][i], CREDIT_PENDING) || 
       !mycmp(ledger->text_content[0][i], CREDIT_CLEARED) ||
       !mycmp(ledger->text_content[0][i], NOTTHEREYET) || 
       !mycmp(ledger->text_content[0][i], PENDING)){
      fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s", ledger->text_content[0][i],
              ledger->text_content[1][i], ledger->text_content[2][i],
              ledger->text_content[3][i], ledger->text_content[4][i],
              ledger->text_content[5][i]);
      for(j = 0; j < ledger->nbank; ++j)
        if(!mycmp(ledger->text_content[3][i], ledger->bank[j]))
          for(k = 0; k < ledger->npartition[i]; ++k)
            if(!mycmp(ledger->text_content[4][i], ledger->partition[j][k]))
              ledger->partition_totals[j][k] -= atof(ledger->text_content[1][i]);
      
    }
  } 
  
  for(i = 0; i < ledger->nbank; ++i)
    for(j = 0; j < ledger->npartition[i]; ++j)
      if(abs(ledger->partition_totals[i][j]) > eps)
        fprintf(fp, "\n\t%0.2f\t\t%s\t%s\tcondensed", ledger->partition_totals[i][j], 
                ledger->bank[i], ledger->partition[i][j]);
      
  fclose(fp);
  free_ledger(ledger);
  return 0;
}

void usage(){
  printf("\nUsage:\n$ ./ledger [REQUIRED_INPUT_LEDGER] [OPTIONAL_OUTPUT_CONDENSED_LEDGER]\n\n");
  printf("See README.txt for details.\n");
}

int standalone(int argc, char **argv){
  FILE *fp;
  
  if(argc < 2){
    usage();
    return 0;
  }
  
  if(argc >= 2){
    fp = fopen(argv[1], "r");
    if(fp == NULL){
      fprintf(stderr, "Error: cannot open input file, %s.\nPossible reason: file does not exist.\n", argv[1]);
      return 1;
    } 
    fclose(fp);
   
    if(summarize(argv[1])){
      printf("Exiting due to failure.\n\n");
      return 1;
    }
  }
  
  if(argc == 3){
    fp = fopen(argv[2], "r");
    if(fp == NULL){
      fprintf(stderr, "Error: cannot open output file, %s.\nPossible reason: inadequate permissions.\n", argv[2]);
      return 1;
    } 
    fclose(fp);
   
    if(condense(argv[1], argv[2])){
      printf("Exiting due to failure.\n\n");
      return 1;
    }
  }
  
  return 0;
}

int main(int argc, char **argv){
  return standalone(argc, argv) ? EXIT_FAILURE : EXIT_SUCCESS;
}
