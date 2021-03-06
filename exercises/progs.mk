CC = gcc
CFLAGS = -O3 -g -pedantic -std=c89 -Wall -Wextra
LDFLAGS = -lm

COMPILE = $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

bin:
	mkdir -p ./bin/

clean:
	rm -rf ./bin/
