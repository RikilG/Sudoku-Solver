#include "Cell.h"
#include "Board.h"
#include <cstdio>

void Board::printBoard() {
    for(int i=0;i<boardSide;i++) {
        if(i%3 == 0) {
            std::printf("+---------+---------+---------+\n");
        }
        for(int j=0;j<boardSide;j++) {
            if(j%3 == 0)
                std::printf("|");
            std::printf(" %d ", grid[i][j].getValue());
        }
        std::printf("|\n");
    }
    std::printf("+---------+---------+---------+\n");
}