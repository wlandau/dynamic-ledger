#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

#define F "../data/ledgers/simple.txt"

int main(){
  Ledger *ledger = NULL;
  int **coords;
  char entrynumber[] = "9";
  char entrystr[] = "  sacrebleu!";
  int i;
  
  coords = malloc(2 * sizeof(int*));
  for(i = 0; i < 2; ++i)
    coords[i] = malloc(6 * sizeof(int));
  
  coords[0][0] = -1;
  coords[0][1] = 0;
  coords[0][2] = 0;
  coords[0][3] = 2; 
  coords[0][4] = 3;
  coords[0][5] = 10;

  coords[1][0] = -1;
  coords[1][1] = 0;
  coords[1][2] = 1;
  coords[1][3] = 2; 
  coords[1][4] = 4;
  coords[1][5] = 10;  
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("1 RET = %d\n", map_to_coords_colmajor(ledger, entrynumber, coords, 6, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("2 RET = %d\n", map_to_coords_colmajor(ledger, entrynumber, coords, 0, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
 
  printf("3 RET = %d\n", map_to_coords_colmajor(ledger, entrynumber, coords, 6, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("4 RET = %d\n", map_to_coords_colmajor(ledger, entrynumber, coords, 6, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  
  printf("4 RET = %d\n", map_to_coords_colmajor(ledger, entrystr, coords, 6, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("5 RET = %d\n", map_to_coords_colmajor(ledger, entrystr, coords, 6, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  
  printf("6 RET = %d\n", map_to_coords_colmajor(ledger, entrystr, coords, 6, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("7 RET = %d\n", map_to_coords_colmajor(ledger, entrystr, coords, 6, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  for(i = 0; i < 2; ++i)
    free(coords[i]);
  free(coords);
  
  free_ledger(&ledger);

  return 0;
}
