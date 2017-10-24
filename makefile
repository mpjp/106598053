all: hw4

hw4: MainList.o Atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 MainList.o Atom.o -lgtest
else
	g++ -o hw4 MainList.o Atom.o -lgtest -lpthread
endif

Atom.o: Atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c Atom.cpp
MainList.o: MainList.cpp utList.h atom.h
	g++ -std=gnu++0x -c MainList.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw4
endif

