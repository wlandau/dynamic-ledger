for i in `ls`
do
  make --silent -C $i
  cd $i
  valgrind ./test 2>> ../stderr.txt
  cd ..
done