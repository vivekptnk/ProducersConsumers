CC=gcc
CFLAGS=-ggdb -Wall -pthread

test : prodcons
	date > results.txt
	./prodcons 
	./prodcons 50 5000
	./prodcons 5000 50
	
checkMem : prodcons
	date > results.txt
	echo "checking memory" >> results.txt
	valgrind --leak-check=full --show-leak-kinds=all ./prodcons 5 10 | tee -a results.txt
	
prodcons_trace : prodcons.c
	${CC} ${CFLAGS} -DTRACE -o prodcons prodcons.c
	
clean :
	-rm prodcons results.txt
