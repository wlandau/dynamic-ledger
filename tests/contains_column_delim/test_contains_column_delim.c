#include <errno.h>
#include <getopt.h>
#include <ledger.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <user_settings.h>

int main(){
  printf("\"%s\" contains column delimiter. ret = %d\n", "	hi", contains_tabs("	hi"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "hi	",  contains_tabs("hi	"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "hi	hi",  contains_tabs("hi	hi"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "	hi	hi",  contains_tabs("	hi	hi"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "hi	hi	",  contains_tabs("hi	hi	"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "\thi",  contains_tabs("\thi"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "hi\t", contains_tabs("hi\t"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "hi\thi", contains_tabs("hi\thi"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "\thi\thi", contains_tabs("\thi\thi"));
  printf("\"%s\" contains column delimiter.ret = %d\n", "hi\thi\t", contains_tabs("hi\thi\t"));
  printf("\"%s\" does not contain column delimiter. ret = %d\n", "blkjadlkfj\n", contains_tabs("blkjadlkfj\n"));
  return 0;
}
