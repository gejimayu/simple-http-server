CC = gcc
OBJECTS = server.o

all: server

server.o: server.c
	$(CC) -c server.c

server: $(OBJECTS)
	$(CC) $(OBJECTS) -o server

clean:
	rm -f *.o server

run-500b:
	valgrind --tool=massif --time-unit=ms ./server index500b.html

run-20KB:
	valgrind --tool=massif --time-unit=ms ./server index20KB.html