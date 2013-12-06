git pull
make -C ..

valgrind ../ledger-txt bad.txt
valgrind ../ledger-txt bad.txt con.txt
valgrind ../ledger-txt con.txt 

valgrind ../ledger-txt empty.txt
valgrind ../ledger-txt empty.txt con.txt
valgrind ../ledger-txt con.txt 

valgrind ../ledger-txt example_ledger.txt
valgrind ../ledger-txt example_ledger.txt con.txt
valgrind ../ledger-txt con.txt 

valgrind ../ledger-txt nonnull.txt
valgrind ../ledger-txt nonnull.txt con.txt
valgrind ../ledger-txt con.txt 

valgrind ../ledger-txt justheader.txt
valgrind ../ledger-txt justheader.txt con.txt
valgrind ../ledger-txt con.txt 

valgrind ../ledger-txt tests.sh
valgrind ../ledger-txt tests.sh con.txt
valgrind ../ledger-txt con.txt 

valgrind ../ledger-txt ssdflks
valgrind ../ledger-txt adld con.txt
valgrind ../ledger-txt con.txt 
