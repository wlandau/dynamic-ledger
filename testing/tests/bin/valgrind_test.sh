DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/summaries
mkdir -p $DIR/condensed

valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/bad.txt &> summaries/bad.txt 
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/bad2.txt &> summaries/bad2.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/basic.txt &> summaries/basic.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/empty.txt &> summaries/empty.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/example_ledger.txt &> summaries/example_ledger.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/justbank.txt &> summaries/justbank.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/justcredit.txt &> summaries/justcredit.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/nonnull.txt &> summaries/nonnull.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/small.txt &> summaries/small.txt

valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/bad.txt condensed/bad.txt 2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/bad2.txt  condensed/bad2.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/basic.txt  condensed/basic.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/empty.txt  condensed/empty.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/example_ledger.txt  condensed/example_ledger.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/justbank.txt  condensed/justbank.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/justcredit.txt  condensed/justcredit.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/nonnull.txt  condensed/nonnull.txt  2>> stderr.txt
valgrind ../../../bin/ledger-txt ../../ledgers/ledgers/small.txt  condensed/small.txt  2>> stderr.txt

#diff ../../ledgers/condensed/bad.txt condensed/bad.txt
#diff ../../ledgers/condensed/bad2.txt condensed/bad2.txt
diff ../../ledgers/condensed/basic.txt condensed/basic.txt
diff ../../ledgers/condensed/empty.txt condensed/empty.txt
diff ../../ledgers/condensed/example_ledger.txt condensed/example_ledger.txt
diff ../../ledgers/condensed/justbank.txt condensed/justbank.txt
diff ../../ledgers/condensed/justcredit.txt condensed/justcredit.txt
diff ../../ledgers/condensed/nonnull.txt condensed/nonnull.txt
diff ../../ledgers/condensed/small.txt condensed/small.txt