all: test

test: test_bad_output_file.o bad_output_file.o
	gcc test_bad_output_file.o bad_output_file.o -o test

test_bad_output_file.o:
	gcc -c test_bad_output_file.c -o test_bad_output_file.o -Wall -ansi -pedantic -I../../../include

bad_output_file.o:
	gcc -c ../../../src/bad_output_file.c -o bad_output_file.o -Wall -ansi -pedantic -I../../../include

clean:
	rm *.o
	rm test