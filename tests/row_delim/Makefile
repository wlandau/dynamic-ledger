all: test

test: test_row_delim.o row_delim.o
	gcc test_row_delim.o row_delim.o -o test

test_row_delim.o:
	gcc -c test_row_delim.c -o test_row_delim.o -Wall -ansi -pedantic -I../../include

row_delim.o:
	gcc -c ../../src/row_delim.c -o row_delim.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test