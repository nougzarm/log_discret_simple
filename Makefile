PROG = test

OBJS = test.o log_discret.o
CC = gcc
CPFLAGS = -Wall -Wpointer-arith -O2


test: test.o log_discret.o
	$(CC) $(CPFLAGS) -o test  test.o log_discret.o -lm

test.o: log_discret.h test.h test.c
	$(CC) $(CPFLAGS) -c test.c

log_discret.o: log_discret.c log_discret.h
	$(CC) $(CPFLAGS) -c log_discret.c

clean:
	rm -f $(OBJS)


