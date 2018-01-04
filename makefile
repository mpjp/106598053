all: hw7

hw8: MainIterator.o Atom.o Struct.o Term.o List.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 MainIterator.o Atom.o Struct.o Term.o List.o -lgtest
else
	g++ -o hw7 MainIterator.o Atom.o Struct.o Term.o List.o -lgtest -lpthread
endif

List.o :List.cpp list.h
	g++ -std=gnu++0x -c List.cpp
Atom.o: Atom.cpp atom.h variable.h
	g++ -std=gnu++0x -c Atom.cpp
Struct.o: Struct.cpp struct.h
	g++ -std=gnu++0x -c Struct.cpp
Term.o: Term.cpp term.h
	g++ -std=gnu++0x -c Term.cpp

# MainList.o: MainList.cpp utList.h atom.h
# 	g++ -std=gnu++0x -c MainList.cpp
# MainScanner.o:  MainScanner.cpp scanner.h  #utScanner.h
# 		g++ -std=gnu++0x -c MainScanner.cpp
# MainParser.o: MainParser.cpp parser.h atom.h
# 		g++ -std=gnu++0x -c MainParser.cpp
MainIterator.o: MainIterator.cpp utIterator.h Atom.o
		g++ -std=gnu++0x -c MainIterator.cpp


# list.h atom.h

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif
