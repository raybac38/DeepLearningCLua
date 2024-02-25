CC = gcc
CFLAGS = -Wall -Wextra -g

all: main

main: main.o matrice.o image.o classement.o network.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c matrice.h
	$(CC) $(CFLAGS) -c $<

matrice.o: matrice.c matrice.h
	$(CC) $(CFLAGS) -c $<

image.o: image.c image.h
	$(CC) $(CFLAGS) -c $<

classement.o: classement.c classement.h network.h
	$(CC) $(CFLAGS) -c $<

network.o: network.c network.h matrice.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o main
