CC=gcc
CFLAGS=-g -Wall -Werror -Wextra
FFLAGS=-fpic
SFLAGS=-shared

liblist.so: liblist.o
	$(CC) $(SFLAGS) -o liblist.so liblist.o

liblist.o: liblist.c 
	$(CC) -c $(CFLAGS) $(FFLAGS) liblist.c

.PHONY: clean install uninstall all

install: liblist.so
	cp liblist.so /usr/lib
	chmod 0755 /usr/lib/liblist.so
	cp liblist.h /usr/include
	ldconfig

uninstall:
ifneq (,$(wildcard /usr/lib/liblist.so))
	rm /usr/lib/liblist.so
endif
ifneq (,$(wildcard /usr/include/liblist.h))
	rm /usr/include/liblist.h
	ldconfig
endif

all: uninstall install clean

clean:
	rm *.o *.so
