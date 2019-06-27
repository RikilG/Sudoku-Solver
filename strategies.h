#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "Board.h"

extern int valuesSet;
const int boardSide = 9;

int backtracking(Board& board);
int nakedSingle(Board& board);
int hiddenSingle(Board& board);
int blkColRowInteractions(Board& board);
// checking sudoku is not a solving strategy, but just for the sake of checking :)
bool checkSudoku(Board& board);

#endif