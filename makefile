all: hw5

hw5: MainParser.o Atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 MainParser.o Atom.o -lgtest
else
	g++ -o hw5 MainParser.o Atom.o -lgtest -lpthread
endif


Atom.o: Atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c Atom.cpp
MainList.o: MainList.cpp utList.h atom.h
	g++ -std=gnu++0x -c MainList.cpp
MainScanner.o:  MainScanner.cpp scanner.h  #utScanner.h
		g++ -std=gnu++0x -c MainScanner.cpp
MainParser.o: MainParser.cpp parser.h atom.h
		g++ -std=gnu++0x -c MainParser.cpp



clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
