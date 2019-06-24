solver: Cell.o Board.o main.o
	g++ Cell.o Board.o main.o -o solver

main.o: main.cpp
	g++ -c main.cpp

Cell.o: Cell.h Cell.cpp
	g++ -c Cell.cpp

Board.o: Board.h Board.cpp
	g++ -c Board.cpp

clean: 
	rm *.o solver

target: dependancies
	command