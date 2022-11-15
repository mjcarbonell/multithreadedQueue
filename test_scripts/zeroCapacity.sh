
cleanup(){
	rm -r test_dir
}

QUEUE="queue.o queue.h"
TEST_FILES="../test_files/zeroCapacity.c ../test_files/Makefile"

mkdir test_dir

cp $QUEUE test_dir
cp  $TEST_FILES test_dir

make -C test_dir

timeout 5 ./test_dir/queue-test

if [ $? > 0 ] # if greater than zero we never reached the end and we can return zero 
# knowing that the c program indefinely was hanging because the queue had a capacity of zero 
then
	cleanup
	exit 0
else
	exit 1
fi

cleanup
