all: test

test: test_row_delim_char.o row_delim_char.o
	gcc test_row_delim_char.o row_delim_char.o -o test

test_row_delim_char.o:
	gcc -c test_row_delim_char.c -o test_row_delim_char.o -Wall -ansi -pedantic -I../../include

row_delim_char.o:
	gcc -c ../../src/row_delim_char.c -o row_delim_char.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test