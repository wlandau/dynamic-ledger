DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

mkdir -p $DIR/data/summaries
mkdir -p $DIR/data/condensed

if [ -f $DIR/stderr.txt ]
then
  rm $DIR/stderr.txt
fi

for l in `ls $DIR/data/ledgers/*.txt`
do
  f=`basename $l`
  $DIR/../ledger $DIR/data/ledgers/$f &> $DIR/data/summaries/$f                                        
  $DIR/../ledger $DIR/data/ledgers/$f $DIR/data/condensed/$f 2>> $DIR/stderr.txt                       
done