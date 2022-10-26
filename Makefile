SRC=curler.cpp
BIN=curler
CFLAGS=-Wextra -Wall
CC=g++
LDFLAGS=$(shell pkg-config --libs libcurl)

default:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)

install:
	$(shell mv curler /usr/bin/)

clean:
	$(shell rm curler)

uninstall:
	$(shell rm /usr/bin/curler)
