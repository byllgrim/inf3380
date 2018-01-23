CC = gcc
CFLAGS = -O3 -pedantic -std=c89 -Wall -Wextra
LDFLAGS = -lm

COMPILE = $(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

all: bin bin/limit bin/1d_rand

bin/limit: limit.c
	$(COMPILE)

bin/1d_rand: 1d_rand.c
	$(COMPILE)

bin:
	mkdir -p ./bin/

clean:
	rm -rf ./bin/
