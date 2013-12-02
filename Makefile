all:
	gcc -Wall -pedantic -ansi ledger.c -o ledger

clean:
	rm ledger