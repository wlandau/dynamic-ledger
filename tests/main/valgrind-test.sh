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
  valgrind $DIR/../../dl $DIR/../data/ledgers/$f 1> $DIR/summaries/$f 2>> $DIR/stderr.txt
  valgrind $DIR/../../dl $DIR/../data/ledgers/$f $DIR/condensed/$f 2>> $DIR/stderr.txt
done