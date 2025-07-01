CC=g++
CFLAGS=-Wall -c -g
LFLAGS=-Wall -g

all: programma

programma: compito.o bst.o carta.o
	$(CC) $(LFLAGS) compito.o bst.o carta.o -o programma

compito.o: compito.cc bst.h carta.h
	$(CC) $(CFLAGS) compito.cc

bst.o: bst.cc bst.h carta.h
	$(CC) $(CFLAGS) bst.cc

carta.o: carta.cc carta.h
	$(CC) $(CFLAGS) carta.cc

clean:
	rm -f *.o programma 