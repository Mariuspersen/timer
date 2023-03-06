CC		= gcc
CFLAGS	=  -Wextra -Wall -std=c11 -pedantic

make:
	${CC} ${CFLAGS} ${DBUS} -O2 -o timer timer.c

debug:
	${CC} ${CFLAGS} ${DBUS} -ggdb -o timer_debug timer.c

clean:
	rm -f timer

install: make
	mkdir -p /bin
	cp -f timer /bin
	chmod 755 /bin/timer

uninstall:
	rm -f /bin/timer
