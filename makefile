
all: hw3

hw3: MainVariable.o Term.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 MainVariable.o Term.o -lgtest
else
	g++ -o hw3 MainVariable.o Term.o -lgtest -lpthread
endif

MainVariable.o: MainVariable.cpp utVariable.h
		g++ -std=gnu++0x -c MainVariable.cpp
Term.o: Term.cpp term.h
		g++ -std=gnu++0x -c Term.cpp

# Atom.o: Atom.cpp atom.h
# 		g++ -std=gnu++0x -c Atom.cpp
# Variable.o: Variable.cpp variable.h
# 		g++ -std=gnu++0x -c Variable.cpp
# Number.o: Number.cpp number.h  #atom.h
# 		g++ -std=gnu++0x -c Number.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif  #






#exp: mainExp.o
#	g++ -o exp mainExp.o -lgtest -lpthread
#mainExp.o: mainExp.cpp exp.h global.h
#	g++ -std=c++11 -c mainExp.cpp

#utScannerParser: mainScannerParser.o term.o struct.o var.o list.o
#	g++ -o utScannerParser mainScannerParser.o term.o var.o struct.o list.o -lgtest -lpthread
#mainScannerParser.o: mainScannerParser.cpp utScanner.h utParser.h scanner.h parser.h term.h var.h struct.h list.h global.h node.h
#		g++ -std=c++11 -c mainScannerParser.cpp

#utTerm: mainTerm.o term.o struct.o var.o list.o
#	g++ -o utTerm mainTerm.o term.o var.o struct.o list.o -lgtest -lpthread
#mainTerm.o: mainTerm.cpp utTerm.h term.h var.h utStruct.h struct.h list.h utList.h
#	g++ -std=c++11 -c mainTerm.cpp
#term.o: term.h term.cpp
#	g++ -std=c++11 -c term.cpp
#struct.o: struct.h struct.cpp
#	g++ -std=c++11 -c struct.cpp
#var.o: var.h var.cpp
#g++ -std=c++11 -c var.cpp
#list.o: list.h list.cpp term.h var.h
#	g++ -std=c++11 -c list.cpp


# clean:
# 	rm -f *.o utAtom utVariable utStruct
# stat:
# 	wc *.h *.cpp
