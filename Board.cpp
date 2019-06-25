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
    std::cout << "affected elements after naked single : " << valuesSet << "\n";
    hiddenSingle(*this); // requires nakedSingle to run atleast once to rule out row/col/block illegal values
    std::cout << "affected elements after hidden single: " << valuesSet << "\n";
}

bool Board::checkValue(int x, int y, int ans) {
    return grid[x][y].getValue() == ans;
}