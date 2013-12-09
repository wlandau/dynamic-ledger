all: test

test: test_contains_column_delim.o contains_column_delim.o
	gcc test_contains_column_delim.o contains_column_delim.o -o test

test_contains_column_delim.o:
	gcc -c test_contains_column_delim.c -o test_contains_column_delim.o -Wall -ansi -pedantic -I../../include

contains_column_delim.o:
	gcc -c ../../src/contains_column_delim.c -o contains_column_delim.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test