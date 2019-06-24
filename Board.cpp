#include "Cell.h"
#include "Board.h"
#include "strategies.h"
#include <iostream>
#include <vector>

void Board::printBoard() {
    for(int i=0;i<boardSide;i++) {
        if(i%3 == 0) {
            std::cout << "+---------+---------+---------+\n";
        }
        for(int j=0;j<boardSide;j++) {
            if(j%3 == 0)
                std::cout << "|";
            std::cout << " " << grid[i][j].getValue() << " ";
        }
        std::cout << "|\n";
    }
    std::cout << "+---------+---------+---------+\n\n";
}

void Board::solveBoard() {
    nakedSingle(*this);
}