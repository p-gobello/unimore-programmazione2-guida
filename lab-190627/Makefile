CC = g++
CFLAGS = -Wall -g

all: main

main: main.o grafo.o liste.o
	$(CC) $(CFLAGS) -o main main.o grafo.o liste.o

main.o: main.cc grafo.h liste.h tipo.h
	$(CC) $(CFLAGS) -c main.cc

grafo.o: grafo.cc grafo.h tipo.h
	$(CC) $(CFLAGS) -c grafo.cc

liste.o: liste.cc liste.h tipo.h
	$(CC) $(CFLAGS) -c liste.cc

clean:
	rm -f *.o main
