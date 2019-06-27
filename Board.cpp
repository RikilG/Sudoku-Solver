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
    printBoard();
    hiddenSingle(*this); // requires nakedSingle to run atleast once to rule out row/col/block illegal values
    std::cout << "affected elements after hidden single: " << valuesSet << "\n";
    printBoard();
    backtracking(*this);
    bool check = checkSudoku(*this);
    if(check)
        std::cout << ">>> Sudoku Solution Correct!!\n";
    else
        std::cout << ">>> Sudoku Solution INCORRECT\n";
}

bool Board::checkValue(int x, int y, int ans) {
    return grid[x][y].getValue() == ans;
}

int Board::getBlockNo(int rowNo, int colNo) {
    int blockRow = rowNo/3;
    int blockCol = colNo/3;
    return 3*blockRow + blockCol;
}

//--------------------------Block-functions-----------------------------------------------------------

std::vector<int> Board::Block::getValues() {
    std::vector<int> values;
    for(int i=startRow;i<startRow+3;i++) {
        for(int j=startCol;j<startCol+3;j++) {
            if((*parent).grid[i][j].hasValue()) {
                values.push_back((*parent).grid[i][j].getValue());
            }
        }
    }
    return values;
}

int Board::Block::getBlockNo() {
    return (*parent).getBlockNo(startRow, startCol);
}