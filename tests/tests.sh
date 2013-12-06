git pull
make -C ..

valgrind ../ledger bad.txt
valgrind ../ledger bad.txt con.txt
valgrind ../ledger con.txt 

valgrind ../ledger empty.txt
valgrind ../ledger empty.txt con.txt
valgrind ../ledger con.txt 

valgrind ../ledger example_ledger.txt
valgrind ../ledger example_ledger.txt con.txt
valgrind ../ledger con.txt 

valgrind ../ledger nonnull.txt
valgrind ../ledger nonnull.txt con.txt
valgrind ../ledger con.txt 

valgrind ../ledger justheader.txt
valgrind ../ledger justheader.txt con.txt
valgrind ../ledger con.txt 

valgrind ../ledger tests.sh
valgrind ../ledger tests.sh con.txt
valgrind ../ledger con.txt 

valgrind ../ledger ssdflks
valgrind ../ledger adld con.txt
valgrind ../ledger con.txt 
