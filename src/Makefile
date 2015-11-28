# Makefile for fractranC

CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -O3 
LIBS =
OBJS = fractranC.o Output.o Token.o Prime.o
MAIN = fractranC

all: $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) -o $(MAIN) $(CFLAGS) $(OBJS) $(LIBS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) *.o $(MAIN)

.PHONY: all clean

