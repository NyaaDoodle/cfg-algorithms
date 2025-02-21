CC=gcc
CFLAGS=-Wall -std=c99
PROGNAME=cfg_algo

make: main.c vertexlist.c cfg.c vertexset.c algorithms.c
	$(CC) main.c vertexlist.c cfg.c vertexset.c algorithms.c $(CFLAGS) -o $(PROGNAME)

clean:
	rm $(PROGNAME)
