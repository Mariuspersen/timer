CC		= gcc
CFLAGS	= -Wextra -Wall -std=c11 -pedantic

make:
	${CC} ${CFLAGS} -O2 -o timer timer.c

debug:
	${CC} ${CFLAGS} -ggdb -o timer_debug timer.c

clean:
	rm -f timer
	rm -f timer_debug
	
install: make
	mkdir -p /bin
	cp -f timer /bin
	chmod 755 /bin/timer

uninstall:
	rm -f /bin/timer
