CC=gcc
CFlags=-g -Wall
BINS=server

all: $(BINS)

%: %.c
	$(CC) $(CFlags) -o $@  $^ -lpthread

clean:
	rm -f *.dSYM $(BINS)