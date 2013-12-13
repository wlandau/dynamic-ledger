all: test

test: test_output_file.o output_file.o
	gcc test_output_file.o output_file.o -o test

test_output_file.o:
	gcc -c test_output_file.c -o test_output_file.o -Wall -ansi -pedantic -I../../include

output_file.o:
	gcc -c ../../src/output_file.c -o output_file.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test