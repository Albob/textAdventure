CC=gcc
CFLAGS=-g -Wall -I./Iib -Lalbob
TARGET=textAdventure

textAdventure: libalbob.a main.c
	${CC} ${CFLAGS} main.c -o ${TARGET}

build/string.o: lib/albob/string.h lib/albob/string.c
	${CC} ${CFLAGS} -c lib/albob/string.c -o build/string.o

libalbob.a: build/string.o
	ar ruv libalbob.a build/string.o
	ranlib libalbob.a

clean-all: 
	rm -fr ${TARGET}
	rm -fr *.o
	rm -fr build/*
