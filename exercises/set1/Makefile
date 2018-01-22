TARGS = limit

LDFLAGS = -lm

all: $(TARGS)

$(TARGS): $(TARGS:=.c)
	cc -o $@ $@.c $(LDFLAGS)

clean:
	rm -rf $(TARGS)
