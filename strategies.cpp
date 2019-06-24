#include "strategies.h"
#include "Board.h"
#include <iostream>
#include <vector>
//private function prototypes
int checkRow(int rowNo, Board& board);
int checkCol(int colNo, Board& board);
int checkBlock(int blockNo, Board& board);

const int boardSide = 9;

int nakedSingle(Board& board) {
    int noOfChanges = 0, totalChanges = 0;
    do {
        noOfChanges = 0;
        for(int i=0;i<boardSide;i++) {
            noOfChanges += checkRow(i, board);
        }
        for(int i=0;i<boardSide;i++) {
            noOfChanges += checkCol(i, board);
        }
        for(int i=0;i<boardSide;i++) {
            noOfChanges += checkBlock(i, board);
        }
        std::cout << "no of changes : " << noOfChanges << "\n";
        totalChanges += noOfChanges;
    } while(noOfChanges > 0);

    // for(int i=0;i<boardSide;i++) {
    //     for(int j=1;j<10;j++) {
    //         std::cout << (grid[0][i].getOptions())[j] << " ";
    //     }
    //     std::cout << "\n";
    // }
    return totalChanges;
}

int hiddenSingle(Board& board) {
    int totalChanges = 0;
    return totalChanges;
}

int blkColRowInteractions(Board& board) {
    int totalChanges = 0;
    return totalChanges;
}

int checkRow(int rowNo, Board& board) {
    int noOfChanges = 0;
    std::vector<int> elements;
    for(int i=0;i<boardSide;i++) {
        if(board.grid[rowNo][i].hasValue()) {
            elements.push_back(board.grid[rowNo][i].getValue());
        }
    }
    for(int i=0;i<boardSide;i++) {
        if(board.grid[rowNo][i].hasValue())
            continue;
        for(int& element: elements) {
            int result = board.grid[rowNo][i].strikeOption(element);
            if(result != False)
                noOfChanges++;
            if(result == VALUE_SET) {
                i = -1;
                elements.push_back(board.grid[rowNo][i].getValue());
                break;
            }
        }
    }
    return noOfChanges;
}

int checkCol(int colNo, Board& board) {
    int noOfChanges = 0;
    std::vector<int> elements;
    for(int i=0;i<boardSide;i++) {
        if(board.grid[i][colNo].hasValue()) {
            elements.push_back(board.grid[i][colNo].getValue());
        }
    }
    for(int i=0;i<boardSide;i++) {
        if(board.grid[i][colNo].hasValue())
            continue;
        for(int& element: elements) {
            int result = board.grid[i][colNo].strikeOption(element);
            if(result != False)
                noOfChanges++;
            if(result == VALUE_SET) {
                i = -1;
                elements.push_back(board.grid[i][colNo].getValue());
                break;
            }
        }
    }
    return noOfChanges;
}

int checkBlock(int blockNo, Board& board) {
    int x = (blockNo%3)*3;
    int y = (blockNo/3)*3;    // Theese x,y coordinates point to first element of corresponding block.
    int noOfChanges = 0;
    std::vector<int> elements;
    for(int i=x;i<x+3;i++) {
        for(int j=y;j<y+3;j++) {
            if(board.grid[i][j].hasValue()) {
                elements.push_back(board.grid[i][j].getValue());
            }
        }
    }
    LABEL_BLOCK_CHECK:
    for(int i=x;i<x+3;i++) {
        for(int j=y;j<y+3;j++) {
            for(int& element: elements) {
                int result = board.grid[i][j].strikeOption(element);
                if(result != False) {
                    noOfChanges++;
                }
                if(result == VALUE_SET) {
                    goto LABEL_BLOCK_CHECK;   // have to use goto to break all loops and goto first for loop(break dosent work);
                }
            }
        }
    }
    return noOfChanges;
}