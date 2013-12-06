all: ledger-txt

ledger: ledger-txt.c
	gcc -Wall -pedantic -ansi ledger.c -o ledger-txt

clean:
	rm ledger-txt