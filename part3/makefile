CC=gcc
CFlags=-g -Wall
BINS=server
OBJS=server.o myqueue.o

all: $(BINS)

server: $(OBJS)
	$(CC) $(CFlags) -o $@  $^ -lpthread

%: %.c
	$(CC) $(CFlags) -c -o $@  $^ -lpthread

clean:
	rm -f *.dSYM $(BINS) *.o