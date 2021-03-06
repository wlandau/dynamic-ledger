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
  
  coords = malloc(6 * sizeof(int*));
  for(i = 0; i < 6; ++i)
    coords[i] = malloc(2 * sizeof(int));
  
  coords[0][0] = -1;
  coords[1][0] = 0;
  coords[2][0] = 0;
  coords[3][0] = 2; 
  coords[4][0] = 3;
  coords[5][0] = 10;

  coords[0][1] = -1;
  coords[1][1] = 0;
  coords[2][1] = 1;
  coords[3][1] = 2; 
  coords[4][1] = 4;
  coords[5][1] = 10;  
  
  get_ledger(&ledger, F, NULL, NULL);
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("1 RET = %d\n", map_to_coords_rowmajor(ledger, entrynumber, coords, 6, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("2 RET = %d\n", map_to_coords_rowmajor(ledger, entrynumber, coords, 0, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
 
  printf("3 RET = %d\n", map_to_coords_rowmajor(ledger, entrynumber, coords, 6, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  printf("4 RET = %d\n", map_to_coords_rowmajor(ledger, entrynumber, coords, 6, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  
  printf("4 RET = %d\n", map_to_coords_rowmajor(ledger, entrystr, coords, 6, 0));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("5 RET = %d\n", map_to_coords_rowmajor(ledger, entrystr, coords, 6, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);

  
  printf("6 RET = %d\n", map_to_coords_rowmajor(ledger, entrystr, coords, 6, 2));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  printf("7 RET = %d\n", map_to_coords_rowmajor(ledger, entrystr, coords, 6, 1));
  print_ledger_to_stream(ledger, stdout);
  print_summary_to_stream(ledger, stdout, 1);
  
  for(i = 0; i < 6; ++i)
    free(coords[i]);
  free(coords);
  
  free_ledger(&ledger);

  return 0;
}
