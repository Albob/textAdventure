CC=gcc
CFLAGS=-g -Wall -I./lib -L. -lalbob
LIB=libalbob.a
TARGET=textAdventure

textAdventure: ${LIB} main.c
	${CC} ${CFLAGS} main.c -o ${TARGET}

build:
	mkdir -p build

build/string.o: build lib/albob/string.h lib/albob/string.c
	${CC} ${CFLAGS} -c lib/albob/string.c -o build/string.o

${LIB}: build/string.o
	ar ruv ${LIB} build/string.o
	ranlib ${LIB}

clean-all: 
	rm -fr ${TARGET}
	rm -fr ${LIB}
	rm -fr *.o
	rm -fr build/*
