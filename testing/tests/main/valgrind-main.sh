DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/summaries
mkdir -p $DIR/condensed

if [ -f $DIR/stderr.txt ]
then
  rm $DIR/stderr.txt
fi

for l in `ls $DIR/../../ledgers/ledgers/*.txt`
do
  f=`basename $l`
  valgrind $DIR/../../../bin/ledger-txt $DIR/../../ledgers/ledgers/$f 1> $DIR/summaries/$f 2>> $DIR/stderr.txt
  valgrind $DIR/../../../bin/ledger-txt $DIR/../../ledgers/ledgers/$f $DIR/condensed/$f 2>> $DIR/stderr.txt


  if [ -f $DIR/../../ledgers/condensed/$f && -f $DIR/condensed/$f ]
  then
    diff $DIR/../../ledgers/condensed/$f $DIR/condensed/$f 2>> $DIR/stderr.txt
  fi

  if [ -f $DIR/../../ledgers/summaries/$f && -f $DIR/summaries/$f ]
  then
    diff $DIR/../../ledgers/summaries/$f $DIR/summaries/$f 2>> $DIR/stderr.txt
  fi

done