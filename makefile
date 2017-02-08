CC = g++
CFLAGS = -Wall 
INC = $(shell pkg-config --cflags librtlsdr)
LIB = $(shell pkg-config --libs librtlsdr)
DEBUG = -g
TARGETS = main

.DEFAULT: all

.PHONY: all debug clean

all: $(TARGETS)

debug: CFLAGS += $(DEBUG)
debug: clean $(TARGETS)

main: main.cpp main.o
	$(CC) $(CFLAGS) $(INC) main.cpp -o main $(LIB)

clean:
	rm -f $(TARGETS) *.o output.bin
