CC = gcc 
CFLAGS = -std=c17 -Wall -Wextra  -Werror -Wpedantic -g
# -Werror
#all: client 

#client: client.o queue.o 
#	$(CC) -o client client.o queue.o -lm
#client.o: client.c 
#	$(CC) $(CFLAGS) -c client.c
queue.o: queue.c
	$(CC) $(CFLAGS) -c queue.c

clean:
	rm -f client queue.o 

scan-build: clean
	scan-build make   
	
format: 
	clang-format -i -style=file queue.c 
check:
	valgrind --leak-check=full ./client
	
that: 
	./client
