#include "strategies.h"
#include "Board.h"
#include <iostream>
#include <vector>
#include <algorithm>

int valuesSet = 0;

//private function prototypes
int backtrack_recur(Board& board, int rowNo, int colNo);
int nakedSingle_checkRow(int rowNo, Board& board);
int nakedSingle_checkCol(int colNo, Board& board);
int nakedSingle_checkBlock(int blockNo, Board& board);
int hiddenSingle_checkRow(int rowNo, Board& board);
int hiddenSingle_checkCol(int colNo, Board& board);

int backtracking(Board& board) {
    int noOfChanges = 0;
    backtrack_recur(board, 0, 0);
    return noOfChanges;
}

int nakedSingle(Board& board) {
    // checks rows, cols, blocks and fills only possibility cells by crossing off others.
    int noOfChanges = 0, totalChanges = 0;
    do {
        noOfChanges = 0;
        for(int i=0;i<boardSide;i++) {
            noOfChanges += nakedSingle_checkRow(i, board);
        }
        for(int i=0;i<boardSide;i++) {
            noOfChanges += nakedSingle_checkCol(i, board);
        }
        for(int i=0;i<boardSide;i++) {
            noOfChanges += nakedSingle_checkBlock(i, board);
        }
        totalChanges += noOfChanges;
        // std::cout << "changes: " << totalChanges << "\n";
    } while(noOfChanges > 0);
    return totalChanges;
}

int hiddenSingle(Board& board) {
    int totalChanges = 0;
    for(int i=0;i<boardSide;i++) {
        totalChanges += hiddenSingle_checkRow(i, board);
        totalChanges += hiddenSingle_checkCol(i, board);
    }
    return totalChanges;
}

int blkColRowInteractions(Board& board) {
    int totalChanges = 0;
    return totalChanges;
}

bool checkSudoku(Board& board) {
    //check rows and cols
    for(int i=0;i<boardSide;i++) {
        int row[10] = {0};
        int col[10] = {0};
        int block[10] = {0};
        auto blockValues = board.blocks[i].getValues();
        if(blockValues.size() != boardSide)
            return false;
        for(int j=0;j<boardSide;j++) { // get row and col values
            row[ board.grid[i][j].getValue() ] = 1;
            col[ board.grid[j][i].getValue() ] = 1;
            block[ blockValues[j] ] = 1;
        }
        int rowSum = 0, colSum = 0, blockSum = 0;
        for(int k=1;k<=boardSide;k++) {
            rowSum += row[k];
            colSum += col[k];
            blockSum+=block[k];
        }
        if(rowSum!=9 || colSum!=9 || blockSum!=9) {
            return false;
        }
    }
    return true;
}

//-------------------------------Helper-Functions-----------------------------------------------------

int backtrack_optionAvailable(Board& board, int rowNo, int colNo, int value) {
    if(rowNo>=boardSide || colNo>=boardSide || board.grid[rowNo][colNo].hasValue() || value>boardSide)
        return 0;
    for(int i=0;i<boardSide;i++) {
        if(board.grid[rowNo][i].getValue() == value) // found this value somewhere in same row
            return 0;
    }
    for(int i=0;i<boardSide;i++) {
        if(board.grid[i][colNo].getValue() == value) // found this value somewhere in same col
            return 0;
    }
    int blockNo = board.getBlockNo(rowNo, colNo);
    auto blockValues = board.blocks[blockNo].getValues();
    for(int& blockValue: blockValues) {
        if(value == blockValue) {                   // found this value in list of block values
            return 0;
        }
    }
    return 1;
}

int backtrack_setCoords(int& rowNo, int& colNo) {
    if(rowNo<=boardSide-1 && colNo<boardSide-1)
        colNo++;
    else if(colNo==boardSide-1 && rowNo==boardSide-1)
        return 0;
    else if(colNo==boardSide-1) {
        colNo = 0;
        rowNo++;
    }
    return 1;
}

int backtrack_recur(Board& board, int rowNo, int colNo) {
    //base case
    if(rowNo>=boardSide || colNo>=boardSide || board.grid[rowNo][colNo].hasValue())
        return 0;

    //recursion
    auto cellOptions = board.grid[rowNo][colNo].getOptions();
    for(auto& option: cellOptions) {
        if(backtrack_optionAvailable(board, rowNo, colNo, option)) {
            board.grid[rowNo][colNo].setValue(option); // give the cell a possible value
            int nextCoordsPossible;
            int x = rowNo;
            int y = colNo;
            while(x<boardSide && y<boardSide) {
                nextCoordsPossible = backtrack_setCoords(x, y);
                if(nextCoordsPossible == 0) { // no next grid possible and this cell is VALUE_SET
                    return 1;
                }
                if(!board.grid[x][y].hasValue()) {
                    // std::cout << "has value: " << board.grid[rowNo][colNo].getValue() << ", rowNo: " << rowNo << ", colNo: " << colNo << "\n";
                    break;
                }
            }
            if(backtrack_recur(board, x, y) == 1) { //solution found!!
                return 1;
            }
        }
        board.grid[rowNo][colNo].setOptions(cellOptions);
    }
    return 0;
}

int nakedSingle_checkRow(int rowNo, Board& board) {
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
                elements.push_back(board.grid[rowNo][i].getValue());
                i = -1;
                valuesSet++;
                break;
            }
        }
    }
    return noOfChanges;
}

int nakedSingle_checkCol(int colNo, Board& board) {
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
                elements.push_back(board.grid[i][colNo].getValue());
                i = -1;
                valuesSet++;
                break;
            }
        }
    }
    return noOfChanges;
}

int nakedSingle_checkBlock(int blockNo, Board& board) {
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
                    valuesSet++;
                    goto LABEL_BLOCK_CHECK;   // have to use goto to break all loops and goto first for loop(break dosent work);
                }
            }
        }
    }
    return noOfChanges;
}

int hiddenSingle_verifyCell(int rowNo, int colNo, std::vector<int>& commonData, Board& board) {
    auto options = board.grid[rowNo][colNo].getOptions();
    std::vector<int> ans;
    std::set_intersection(options.begin(),options.end(),commonData.begin(),commonData.end(), std::back_inserter(ans));
    if(ans.size()!=1)
        return 0;
    board.grid[rowNo][colNo].setValue(ans[0]);
    valuesSet++;
    return 1;
}

int hiddenSingle_checkRow(int rowNo, Board& board) {
    std::vector<int> v1, v2;
    std::vector<int> commonData;
    int block[3];
    block[0] = board.grid[rowNo][0].hasValue() + board.grid[rowNo][1].hasValue() + board.grid[rowNo][2].hasValue(); // upper block
    block[1] = board.grid[rowNo][3].hasValue() + board.grid[rowNo][4].hasValue() + board.grid[rowNo][5].hasValue(); // middle block
    block[2] = board.grid[rowNo][6].hasValue() + board.grid[rowNo][7].hasValue() + board.grid[rowNo][8].hasValue(); // lower block
    if(!(block[0]==2 || block[1]==2 || block[2]==2))
        return 0;
    int row1,row2;
    switch(rowNo) {
        case 0: row1 = 1;row2 = 2; break;
        case 1: row1 = 0;row2 = 2; break;
        case 2: row1 = 0;row2 = 1; break;
        case 3: row1 = 4;row2 = 5; break;
        case 4: row1 = 3;row2 = 5; break;
        case 5: row1 = 3;row2 = 4; break;
        case 6: row1 = 7;row2 = 8; break;
        case 7: row1 = 6;row2 = 8; break;
        case 8: row1 = 6;row2 = 7; break;
        default:row1 = 1;row2 = 2;
    }
    for(int i=0;i<boardSide;i++) {
        if(board.grid[row1][i].hasValue())
            v1.push_back(board.grid[row1][i].getValue());
        if(board.grid[row2][i].hasValue())
            v2.push_back(board.grid[row2][i].getValue());
    }
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(commonData));
    if(commonData.size() == 0)
        return 0; //use something like break in loop
    for(int i=0;i<3;i++) {
        if(block[i] == 2) {
            for(int j=i*3+0;j<i*3+3;j++) {
                if(!board.grid[rowNo][j].hasValue()) {
                    return hiddenSingle_verifyCell(rowNo,j,commonData,board);
                }
            }
        }
    }
    return 0;
}

int hiddenSingle_checkCol(int colNo, Board& board) {
    std::vector<int> v1, v2;
    std::vector<int> commonData;
    int block[3];
    block[0] = board.grid[0][colNo].hasValue() + board.grid[1][colNo].hasValue() + board.grid[2][colNo].hasValue(); // upper block
    block[1] = board.grid[3][colNo].hasValue() + board.grid[4][colNo].hasValue() + board.grid[5][colNo].hasValue(); // middle block
    block[2] = board.grid[6][colNo].hasValue() + board.grid[7][colNo].hasValue() + board.grid[8][colNo].hasValue(); // lower block
    if(!(block[0]==2 || block[1]==2 || block[2]==2))
        return 0;
    int col1,col2;
    switch(colNo) {
        case 0: col1 = 1;col2 = 2; break;
        case 1: col1 = 0;col2 = 2; break;
        case 2: col1 = 0;col2 = 1; break;
        case 3: col1 = 4;col2 = 5; break;
        case 4: col1 = 3;col2 = 5; break;
        case 5: col1 = 3;col2 = 4; break;
        case 6: col1 = 7;col2 = 8; break;
        case 7: col1 = 6;col2 = 8; break;
        case 8: col1 = 6;col2 = 7; break;
        default:col1 = 1;col2 = 2;
    }
    for(int i=0;i<boardSide;i++) {
        if(board.grid[i][col1].hasValue())
            v1.push_back(board.grid[i][col1].getValue());
        if(board.grid[i][col2].hasValue())
            v2.push_back(board.grid[i][col2].getValue());
    }
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(commonData));
    if(commonData.size() == 0)
        return 0; //use something like break in loop
    for(int i=0;i<3;i++) {
        if(block[i] == 2) {
            for(int j=i*3+0;j<i*3+3;j++) {
                if(!board.grid[j][colNo].hasValue()) {
                    return hiddenSingle_verifyCell(j,colNo,commonData,board);
                }
            }
        }
    }
    return 0;
}