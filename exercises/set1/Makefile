TARGS = limit 1d_rand

CFLAGS = -O3 -pedantic -std=c89 -Wall -Wextra
LDFLAGS = -lm

all: $(TARGS)

$(TARGS): $(TARGS:=.c)
	cc $(CFLAGS) -o $@ $@.c $(LDFLAGS)

clean:
	rm -rf $(TARGS)
