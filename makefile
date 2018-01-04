# all: utAtom utVariable utScanner utIterator shell

all: hw8 shell

hw8: mainScanner.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
	g++ -o hw8 mainScanner.o atom.o list.o struct.o -lgtest -lpthread
mainExpression: mainScanner.cpp scanner.h  atom.h variable.h parser.h
	g++ -std=gnu++0x -c mainScanner.cpp

ifeq (${OS}, Windows_NT)
	g++ -o hw8 mainScanner.o atom.o list.o struct.o -lgtest
else
	g++ -o hw8 mainScanner.o atom.o list.o struct.o -lgtest -lpthread
endif

ifeq (${OS}, Windows_NT)
	g++ -o shell shell.o atom.o list.o struct.o -lgtest
else
	g++ -o shell shell shell.o atom.o list.o struct.o -lgtest -lpthread
endif

mainIterator.o: mainIterator.cpp utIterator.h
	g++ -std=gnu++0x -c mainIterator.cpp




utAtom: mainAtom.o list.o atom.o struct.o
	g++ -o utAtom mainAtom.o atom.o list.o struct.o  -lgtest -lpthread
mainAtom.o: mainAtom.cpp utList.h utAtom.h atom.h utStruct.h struct.h
	g++ -std=gnu++0x -c mainAtom.cpp

atom.o: atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c atom.cpp

utVariable: mainVariable.o atom.o struct.o
		g++ -o utVariable mainVariable.o atom.o struct.o -lgtest -lpthread
mainVariable.o: mainVariable.cpp utVariable.h variable.h
		g++ -std=gnu++0x -c mainVariable.cpp
list.o:list.cpp list.h
		g++ -std=gnu++0x -c list.cpp
struct.o:struct.cpp struct.h
		g++ -std=gnu++0x -c struct.cpp

utScanner: mainScanner.o atom.o list.o struct.o scanner.h utScanner.h utParser.h parser.h
	g++ -o utScanner mainScanner.o atom.o list.o struct.o -lgtest -lpthread
mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h  utParser.h parser.h utExp.h expression.h
		g++ -std=gnu++0x -c mainScanner.cpp
utIterator: mainIterator.o atom.o list.o struct.o iterator.h utIterator.h
	g++ -o utIterator mainIterator.o atom.o list.o struct.o -lgtest -lpthread

shell: shell.o atom.o list.o struct.o parser.h utParser.h
	g++ -o shell shell.o atom.o list.o struct.o -lgtest -lpthread
shell.o:shell.cpp
	g++ -std=gnu++0x -c shell.cpp

clean:
	rm -f *.o utAtom utVariable utScanner shell hw8
stat:
	wc *.h *.cpp
