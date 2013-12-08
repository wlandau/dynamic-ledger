DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

mkdir -p $DIR/ledgers/summaries
mkdir -p $DIR/ledgers/condensed

if [ -f $DIR/stderr.txt ]
then
  rm $DIR/stderr.txt
fi

for l in `ls $DIR/ledgers/ledgers/*.txt`
do
  f=`basename $l`
  $DIR/../ledger $DIR/ledgers/ledgers/$f &> $DIR/ledgers/summaries/$f                                        
  $DIR/../ledger $DIR/ledgers/ledgers/$f $DIR/ledgers/condensed/$f 2>> $DIR/stderr.txt                       
done