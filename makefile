CC=gcc
CFLAGS=-g -Wall -Ilib/ -std=c11
LIB=libalbob.a
GAME=textAdventure
UNITTEST=unitTest

all: ${GAME} ${UNITTEST} 
	echo "Compiling all targets..."

${GAME}: ${LIB} ${GAME}.c
	${CC} ${CFLAGS} -o ${GAME} ${GAME}.c ${LIB}

${UNITTEST}: ${LIB} ${UNITTEST}.c
	${CC} ${CFLAGS} -o ${UNITTEST} ${UNITTEST}.c ${LIB}

build:
	mkdir -p build

build/string.o: build lib/albob/string.h lib/albob/string.c
	${CC} ${CFLAGS} -c lib/albob/string.c -o build/string.o

build/debug.o: build lib/albob/$*.h lib/albob/$*.c
	${CC} ${CFLAGS} -c $*.c -o $@

${LIB}: $(wildcard build/*.o)
	ar ruv ${LIB} $<
	ranlib ${LIB}

.PHONY: clean-all

clean-all: 
	rm -fr ${GAME}
	rm -fr ${LIB}
	rm -fr *.o
	rm -fr build
