all: test

test: test_input_file.o input_file.o
	gcc test_input_file.o input_file.o -o test

test_input_file.o:
	gcc -c test_input_file.c -o test_input_file.o -Wall -ansi -pedantic -I../../include

input_file.o:
	gcc -c ../../src/input_file.c -o input_file.o -Wall -ansi -pedantic -I../../include

clean:
	rm -f *.o
	rm -f test