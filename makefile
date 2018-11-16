# binary, library, object, and source directories
CXX=g++
CC=gcc
OBJ=obj
SRC=src
TARGET=csem

LIBS=`llvm-config --libs core native --ldflags` -lpthread -ldl -lz -ltinfo
CFLAGS=-Wall -g -std=c++11 `llvm-config --cxxflags`

all: yacc objects

HEADERS = $(wildcare include/*.h) $(wildcard include/*.hpp)

CFILES = src/semutil.c src/sym.c src/scan.c
COBJECTS = obj/semutil.o obj/sym.o obj/scan.o

CPPFILES = src/main.cpp src/cgram.cpp src/sem.cpp
CPPOBJECTS = obj/main.o obj/cgram.o obj/sem.o

# Don't delete TARGET or any object file if make is killed or interrupted
.PRECIOUS: $(TARGET) $(CFILES) $(CPPFILES)

yacc:
	yacc -vd src/cgram.y
	mv y.tab.c src/cgram.cpp
	rm y.tab.h y.output

objects: $(HEADERS) $(CPPFILES) $(CFILES)
	$(CC)  -I./include/ -g -c $(CFILES)
	$(CXX) -I./include/ -g -c $(CPPFILES) $(CFLAGS)
	mv *.o obj/
	$(CXX) $(CPPOBJECTS) $(COBJECTS) $(CFLAGS) $(LIBS) -o $(TARGET)
	rm -f *.dwo

build:
	./$(TARGET) < input.c > tmp.ll
	clang tmp.ll -o prog
	rm tmp.ll

test:
	./tests/run.sh

clean:
	rm -f $(TARGET) src/cgram.cpp obj/*.o 
