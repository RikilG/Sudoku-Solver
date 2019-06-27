#ifndef BOARD_H
#define BOARD_H

#include "Cell.h"
#include <vector>

class Board {
    
    class Block {
        private:
        Board *parent;
        int blockNo;
        int startRow;
        int startCol;

        public:
        void init(Board *board, int startRow, int startCol) {
            this->startRow = startRow;
            this->startCol = startCol;
            parent = board;
            blockNo = getBlockNo();
        }
        std::vector<int> getValues();
        int getBlockNo();
    };

    private:
    int boardSide = 9;

    public:
    Cell grid[9][9];
    Block blocks[9];
    Board(int array[][9] = nullptr)
    {
        if(array != nullptr) {
            for(int i=0;i<boardSide;i++) {
                for(int j=0;j<boardSide;j++) {
                    grid[i][j].setValue(array[i][j]);
                }
            }
        }
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                blocks[i*3+j].init(this, i*3, j*3);
            }
        }
    }

    void solveBoard();
    void printBoard();
    bool checkValue(int x, int y, int ans);
    int getBlockNo(int rowNo, int colNo);

};

#endif