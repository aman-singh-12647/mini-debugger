CC=gcc
CFLAGS=-Wall -g
SRC_DIR=src

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(SRCS:.c=.o)

all: debugger

debugger: $(OBJS)
	$(CC) $(CFLAGS) -o debugger $(OBJS)

clean:
	rm -f $(OBJS) debugger