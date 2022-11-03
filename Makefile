SRC=curler.cpp
BIN=curler
CFLAGS=-Wextra -Wall $(shell pkg-config --cflags libnl-3.0)
CC=g++
LDFLAGS=$(shell pkg-config --libs libcurl libnl-3.0)

default:
	$(CC) $(SRC) -o $(BIN) $(CFLAGS) $(LDFLAGS)

install:
	$(shell mv curler /usr/bin/)

clean:
	$(shell rm curler)

uninstall:
	$(shell rm /usr/bin/curler)
