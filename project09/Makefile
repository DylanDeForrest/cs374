CC     = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

all: pc

pc: pc.o eventbuf.o
	$(CC) $(CFLAGS) -o pc pc.o eventbuf.o

pc.o: pc.c eventbuf.h
	$(CC) $(CFLAGS) -c pc.c

eventbuf.o: eventbuf.c eventbuf.h
	$(CC) $(CFLAGS) -c eventbuf.c

clean:
	rm -f pc *.o