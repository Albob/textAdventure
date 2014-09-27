CC=gcc
CFLAGS=-g -Wall -Ilib/ -std=c11
LINK_FLAGS=-L/usr/lib/i386-linux-gnu -I/usr/include -lreadline -lhistory
LIB=libalbob.a
GAME=textAdventure
UNITTEST=unitTest
BUILD_DIR=.build

all: ${GAME} ${UNITTEST} 

${GAME}: ${LIB} ${GAME}.c
	@${CC} ${CFLAGS} -o ${GAME} ${GAME}.c ${LIB} ${LINK_FLAGS}

${UNITTEST}: ${LIB} ${UNITTEST}.c
	@${CC} ${CFLAGS} -o ${UNITTEST} ${UNITTEST}.c ${LIB} ${LINK_FLAGS}

${BUILD_DIR}/string.o: lib/albob/string.c lib/albob/string.h
	@mkdir -p ${BUILD_DIR}
	@${CC} ${CFLAGS} -c $< -o $@

${BUILD_DIR}/debug.o: lib/albob/debug.c lib/albob/debug.h
	@mkdir -p ${BUILD_DIR}
	@${CC} ${CFLAGS} -c $< -o $@

${LIB}: ${BUILD_DIR}/string.o ${BUILD_DIR}/debug.o
	@echo $^
	@ar ruv ${LIB} $^
	@ranlib ${LIB}

.PHONY: clean-tmp

clean-tmp:
	@rm -fr *.swp
	@rm -fr *.bak

clean-all: clean-tmp
	@rm -fr ${GAME}
	@rm -fr ${UNITTEST}
	@rm -fr ${LIB}
	@rm -fr ${BUILD_DIR}
	@rm -fr *.o
	@rm -fr *.dSYM

