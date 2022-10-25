SRC=curler.cpp
BIN=curler
CFLAGS=-Wextra -Wall
CC=g++
LDFLAGS=$(shell pkg-config --libs libcurl)

default:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)

clean:
	$(shell rm curler)
