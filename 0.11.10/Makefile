SRCS = nipper.c
BINPATH = /usr/bin/
CONFPATH = /etc/
MANPATH = /usr/share/man/

all:
	gcc -o nipper $(SRCS) $(LDFLAGS) $(CFLAGS)

install:
	cp nipper $(BINPATH)
	cp nipper.conf $(CONFPATH)
	cp man/nipper.1 $(MANPATH)man1
	cp man/nipper.conf.5 $(MANPATH)man5

uninstall:
	rm -f $(BINPATH)nipper
	rm -f $(CONFPATH)nipper.conf
	rm -f $(MANPATH)man1/nipper.1
	rm -f $(MANPATH)man5/nipper.conf.5

clean:
	rm -f nipper
