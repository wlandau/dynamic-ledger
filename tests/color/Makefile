TEST=test_color

CC=gcc
CCFLAGS=-c -Wall -pedantic -I../../include/
LDFLAGS=-lm
ALLOBJ=$(wildcard ../../obj/*.o)
OBJ=$(filter-out ../../obj/standalone.o, $(ALLOBJ))

all: test

test: $(TEST).o $(OBJ)
	$(CC) $(TEST).o $(OBJ) $(LDFLAGS) -o test

$(TEST).o: $(TEST).c
	$(CC) $(CCFLAGS) $(TEST).c -o $(TEST).o



clean:
	rm -rf *.o
	rm -f  $(BIN)
