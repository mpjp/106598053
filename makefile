
all: hw2

hw2: MainTerm.o Atom.o Number.o Variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 MainTerm.o Atom.o Number.o Variable.o -lgtest
else
	g++ -o hw2 MainTerm.o Atom.o Number.o Variable.o -lgtest -lpthread
endif

MainTerm.o: MainTerm.cpp utTerm.h
		g++ -std=gnu++0x -c MainTerm.cpp
Atom.o: Atom.cpp atom.h
		g++ -std=gnu++0x -c Atom.cpp
Variable.o: Variable.cpp variable.h
		g++ -std=gnu++0x -c Variable.cpp
Number.o: Number.cpp number.h  #atom.h
		g++ -std=gnu++0x -c Number.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif  #
