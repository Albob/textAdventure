CC=gcc
CFLAGS=-g -Wall -Ilib/ -std=c11
LIB=libalbob.a
GAME=textAdventure
UNITTEST=unitTest
BUILD_DIR=.build

all: ${GAME} ${UNITTEST} 

${GAME}: ${LIB} ${GAME}.c
	@${CC} ${CFLAGS} -o ${GAME} ${GAME}.c ${LIB}

${UNITTEST}: ${LIB} ${UNITTEST}.c
	@${CC} ${CFLAGS} -o ${UNITTEST} ${UNITTEST}.c ${LIB}

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

.PHONY: clean-all

clean-all: 
	@rm -fr ${GAME}
	@rm -fr ${UNITTEST}
	@rm -fr ${LIB}
	@rm -fr *.o
	@rm -fr build
