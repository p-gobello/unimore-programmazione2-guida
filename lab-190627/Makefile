CC = g++
CFLAGS = -Wall -g

all: compito

compito: compito.o grafo.o liste.o tipo.o
	$(CC) $(CFLAGS) -o compito compito.o grafo.o liste.o tipo.o

compito.o: compito.cc grafo.h liste.h tipo.h
	$(CC) $(CFLAGS) -c compito.cc

grafo.o: grafo.cc grafo.h tipo.h
	$(CC) $(CFLAGS) -c grafo.cc

liste.o: liste.cc liste.h tipo.h
	$(CC) $(CFLAGS) -c liste.cc

tipo.o: tipo.cc tipo.h
	$(CC) $(CFLAGS) -c tipo.cc

clean:
	rm -f *.o compito
