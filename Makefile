CC=gcc
SOURCES=tester.c common.c encoder.c decoder.c
HEADERS=decoder.h encoder.h common.h
CFLAGS=-g -Wall -std=c99

all: tester

tester: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SOURCES) -o tester

clean:
	rm -f tester
