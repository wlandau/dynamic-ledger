all: test

test: test_col_delim_char.o col_delim_char.o
	gcc test_col_delim_char.o col_delim_char.o -o test

test_col_delim_char.o:
	gcc -c test_col_delim_char.c -o test_col_delim_char.o -Wall -ansi -pedantic -I../../include

col_delim_char.o:
	gcc -c ../../src/col_delim_char.c -o col_delim_char.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test