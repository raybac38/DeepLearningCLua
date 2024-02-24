CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: main.o matrice.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c matrice.h
	$(CC) $(CFLAGS) -c $<

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main
