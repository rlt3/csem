CFLAGS= -g -DLEFTTORIGHT
#CFLAGS= -O -DLEFTTORIGHT
CC=g++

csem:	sym.o scan.o semutil.o cgram.o
	$(CC) $(CFLAGS) -o csem main.cpp sym.o scan.o sem.cpp semutil.o cgram.o `llvm-config --libs core native --cxxflags --ldflags` 

sym.o:	sym.c cc.h sym.h

scan.o:	scan.c cc.h scan.h y.tab.h

#
# NEED TO COMPILE SEM.CPP ALONE BECAUSE llvm FLAGS CAUSE ISSUES WITH HASH TABLE
#sem.o:	sem.c cc.h sem.h semutil.h sym.h

semutil.o: semutil.c cc.h sem.h sym.h

y.tab.h cgram.cpp: cgram.y
	yacc -vd cgram.y
	mv y.tab.c cgram.cpp

clean:
	rm -f csem y.tab.h y.output cgram.cpp sym.o scan.o sem.o semutil.o cgram.o
