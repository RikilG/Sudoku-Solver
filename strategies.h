#ifndef STRATEGIES_H
#define STRATEGIES_H

#include "Board.h"

extern int valuesSet;
const int boardSide = 9;

int nakedSingle(Board& board);
int hiddenSingle(Board& board);
int blkColRowInteractions(Board& board);

#endif