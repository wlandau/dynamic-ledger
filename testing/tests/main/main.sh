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
  $DIR/../../../bin/ledger-txt $DIR/../../ledgers/ledgers/$f &> $DIR/summaries/$f
  $DIR/../../../bin/ledger-txt $DIR/../../ledgers/ledgers/$f $DIR/condensed/$f 2>> $DIR/stderr.txt

  diff $DIR/../../ledgers/condensed/$f $DIR/condensed/$f 2>> $DIR/stderr.txt
  diff $DIR/../../ledgers/summaries/$f $DIR/summaries/$f 2>> $DIR/stderr.txt
done