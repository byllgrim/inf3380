TARGS = limit 1d_rand

CFLAGS = -O3 -pedantic -std=c89 -Wall -Wextra
LDFLAGS = -lm

all: bin/$(TARGS)

bin/$(TARGS): $(TARGS:=.c) bin
	cc $(CFLAGS) -o $@ $< $(LDFLAGS)

bin:
	mkdir -p ./bin/

clean:
	rm -rf $(TARGS)
