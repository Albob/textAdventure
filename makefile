
UNITTEST=unitTest
BUILD_DIR=../../build/textAdventure
SRC_DIR=${PWD}

help:
	@echo "Usage:"
	@echo "   make help:                 Display this message."
	@echo "   make osx:                  Creates an XCode project with the OS X source."
	@echo "   make server:               Launches a server to run the browser version."
	@echo "   make clean-osx-build :     Cleans the XCode project of the OS X version."

osx:
	@echo "SRC_DIR=${SRC_DIR}"
	@mkdir -p ${BUILD_DIR}/osx
	@cd ${BUILD_DIR}/osx; cmake -G Xcode ${SRC_DIR}

.PHONY: clean-tmp

clean-osx-build:
	@rm -fr ${BUILD_DIR}/osx

clean-tmp:
	@rm -fr *.swp
	@rm -fr *.bak

clean-all: clean-tmp clean-osx-build
	@rm -fr ${GAME}
	@rm -fr ${UNITTEST}
	@rm -fr ${LIB}
	@rm -fr ${BUILD_DIR}
	@rm -fr *.o
	@rm -fr *.dSYM
