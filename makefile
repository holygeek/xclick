prefix = /usr/local
FILES = xclick.c xclick.1 LICENSE makefile README
LIBS = `pkg-config --libs x11`
LIBS += -lm
CFLAGS = -Wall

all: xclick

xclick: xclick.c
	$(CC) $(CFLAGS) $(LIBS) $< -o $@

install: xclick
	install -D -m 755 xclick $(prefix)/bin/xclick
	install -D -m 644 xclick.1 $(prefix)/man/man1/xclick.1

clean:
	rm -f xclick

.PHONY: install clean
