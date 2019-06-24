#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

class Board {
    private:
    int boardSide = 9;
    int checkRow(int rowNo);
    int checkCol(int colNo);
    int checkBox(int boxNo);

    public:
    Cell grid[9][9];
    Board(int array[][9] = nullptr)
    {
        if(array != nullptr) {
            for(int i=0;i<boardSide;i++) {
                for(int j=0;j<boardSide;j++) {
                    grid[i][j].setValue(array[i][j]);
                }
            }
        }
    }

    void solveBoard();
    void printBoard();

};

#endif