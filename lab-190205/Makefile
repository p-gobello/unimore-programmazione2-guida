CC = g++
CFLAGS = -Wall -g
OBJS = main.o liste.o tipo.o
TARGET = demazziere

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cc tipo.h liste.h
	$(CC) $(CFLAGS) -c main.cc

liste.o: liste.cc liste.h tipo.h
	$(CC) $(CFLAGS) -c liste.cc

tipo.o: tipo.cc tipo.h
	$(CC) $(CFLAGS) -c tipo.cc

clean:
	rm -f $(OBJS) $(TARGET)
