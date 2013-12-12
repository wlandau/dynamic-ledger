all: test

test: test_column_delim.o column_delim.o
	gcc test_column_delim.o column_delim.o -o test

test_column_delim.o:
	gcc -c test_column_delim.c -o test_column_delim.o -Wall -ansi -pedantic -I../../include

column_delim.o:
	gcc -c ../../src/column_delim.c -o column_delim.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test