TEST=test_legal_amounts

CC=gcc
CCFLAGS=-c -Wall -pedantic -I../../src/
LDFLAGS=-lm
ALLOBJ=$(wildcard ../../src/*.o)
OBJ=$(filter-out ../../src/main.o, $(ALLOBJ))

all: test

test: $(TEST).o $(OBJ)
	$(CC) $(TEST).o $(OBJ) $(LDFLAGS) -o test

$(TEST).o: $(TEST).c
	$(CC) $(CCFLAGS) $(TEST).c -o $(TEST).o



clean:
	rm -rf *.o
	rm -f  $(BIN)
