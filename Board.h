#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"

class Board {
    private:
    Cell grid[9][9];
    int boardSide = 9;

    public:
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

    void printBoard();
};

#endif