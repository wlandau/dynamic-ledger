DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/summaries
mkdir -p $DIR/condensed

if [ -f $DIR/stderr.txt ]
then
  rm $DIR/stderr.txt
fi

for l in `ls $DIR/../data/ledgers/*.txt`
do
  f=`basename $l`
  valgrind $DIR/../../ledger $DIR/../data/ledgers/$f 1> $DIR/summaries/$f 2>> $DIR/stderr.txt
  valgrind $DIR/../../ledger $DIR/../data/ledgers/$f $DIR/condensed/$f 2>> $DIR/stderr.txt

  diff $DIR/../data/ledgers/condensed/$f $DIR/condensed/$f 2>> $DIR/stderr.txt
  diff $DIR/../data/ledgers/summaries/$f $DIR/summaries/$f 2>> $DIR/stderr.txt

done