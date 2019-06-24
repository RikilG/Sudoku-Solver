solver: main.o Cell.o Board.o strategies.o
	g++ Cell.o Board.o main.o strategies.o -o solver

main.o: main.cpp
	g++ -c main.cpp

Cell.o: Cell.h Cell.cpp
	g++ -c Cell.cpp

Board.o: Board.h Board.cpp
	g++ -c Board.cpp

strategies.o: strategies.h strategies.cpp
	g++ -c strategies.cpp

clean: 
	rm *.o solver

target: dependancies
	command