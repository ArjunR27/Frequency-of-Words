CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic

all: fw

fw: hash.o qSort.o fw.o
        $(CC) $(CFLAGS) -o fw hash.o qSort.o fw.o

hash.o: hash.c
        $(CC) $(CFLAGS) -c -o hash.o hash.c
qSort.o: qSort.c
        $(CC) $(CFLAGS) -c -o qSort.o qSort.c
fw.o: fw.c
        $(CC) $(CFLAGS) -c -o fw.o fw.c
clean:
        rm -f *.o
