all: test
	./test

test: test_bad_input_file.o bad_input_file.o
	gcc test_bad_input_file.o bad_input_file.o -o test

test_bad_input_file.o:
	gcc -c test_bad_input_file.c -o test_bad_input_file.o -Wall -ansi -pedantic -I../../../include

bad_input_file.o:
	gcc -c ../../../src/bad_input_file.c -o bad_input_file.o -Wall -ansi -pedantic -I../../../include

clean:
	rm *.o
	rm test