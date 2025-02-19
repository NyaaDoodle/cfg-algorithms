CC=gcc
CFLAGS=-Wall -std=c99
PROGNAME=cfg

make: main.c graph.c
	$(CC) main.c graph.c $(CFLAGS) -o $(PROGNAME)

clean:
	rm $(PROGNAME)
