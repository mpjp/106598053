all: hw4

hw4: MainList.o Atom.o
ifeq (${OS}, Windows_NT)
	g++ -o hw4 MainList.o Atom.o -lgtest
else
	g++ -o hw4 MainList.o Atom.o -lgtest -lpthread
endif

Atom.o: Atom.cpp atom.h variable.h
	g++ -std=c++11 -c Atom.cpp
MainList.o: MainList.cpp utList.h atom.h
	g++ -std=c++11 -c MainList.cpp

clean:
	rm -f *.o hw4
stat:
	wc *.h *.cpp
#
#
# all: madRace utAtom utVariable utScanner
#
#
# madRace: mainMadRace.o
# 	g++ -o madRace mainMadRace.o -lgtest -lpthread
# mainMadRace.o: mainMadRace.cpp madRace.h utMadRace.h
# 	g++ -std=c++11 -c mainMadRace.cpp
#
# utAtom: mainAtom.o atom.o
# 	g++ -o utAtom mainAtom.o atom.o -lgtest -lpthread
# mainAtom.o: mainAtom.cpp utAtom.h atom.h utStruct.h struct.h
# 	g++ -std=c++11 -c mainAtom.cpp
#
# atom.o: atom.cpp atom.h variable.h
# 	g++ -std=c++11 -c atom.cpp
#
# utVariable: mainVariable.o atom.o
# 		g++ -o utVariable mainVariable.o atom.o -lgtest -lpthread
# mainVariable.o: mainVariable.cpp utVariable.h variable.h
# 		g++ -std=c++11 -c mainVariable.cpp
#
#
# utList: MainList.o atom.o
# 		g++ -o utList MainList.o atom.o -lgtest -lpthread
# MainList.o: MainList.cpp utList.h atom.h
# 		g++ -std=c++11 -c MainList.cpp
#
# utScanner: mainScanner.o scanner.h utScanner.h
# 	g++ -o utScanner mainScanner.o -lgtest -lpthread
# mainScanner.o: mainScanner.cpp utScanner.h scanner.h  atom.h struct.h variable.h
# 		g++ -std=c++11 -c mainScanner.cpp
#
# clean:
# 	rm -f *.o madRace utAtom utVariable utScanner
# stat:
# 	wc *.h *.cpp
