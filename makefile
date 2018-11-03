# binary, library, object, and source directories
CXX=g++
CC=gcc
OBJ=obj
SRC=src
TARGET=csem

LIBS=`llvm-config --libs core native --ldflags` -lpthread -ldl -lz -ltinfo
CFLAGS=-Wall -g -std=c++11 `llvm-config --cxxflags`

all: yacc build

HEADERS = $(wildcare include/*.h) $(wildcard include/*.hpp)

CFILES = semutil.c sym.c scan.c
COBJECTS = obj/semutil.o obj/sym.o obj/scan.o

CPPFILES = main.cpp cgram.cpp sem.cpp
CPPOBJECTS = obj/main.o obj/cgram.o obj/sem.o

# Don't delete TARGET or any object file if make is killed or interrupted
.PRECIOUS: $(TARGET) $(CFILES) $(CPPFILES)

yacc:
	yacc -vd cgram.y
	mv y.tab.c cgram.cpp

build: $(HEADERS) $(CPPFILES) $(CFILES)
	$(CC) -g -c $(CFILES)
	$(CXX) -g -c $(CPPFILES) $(CFLAGS)
	mv *.o obj/
	$(CXX) $(CPPOBJECTS) $(COBJECTS) $(CFLAGS) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET) obj/*.o 
