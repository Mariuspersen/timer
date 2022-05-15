CC=clang
CFLAGS=-O2 -Wextra -std=c11 -pedantic

make:
	${CC} ${CFLAGS} -o timer timer.c

clean:
	rm -f timer

install: make
	mkdir -p /bin
	cp -f timer /bin
	chmod 755 /bin/timer

uninstall:
	rm -f /bin/timer
