#include "Board.h"
#include<iostream>

int main() {

    int example[][9] = {
        {0, 6, 3, 0, 0, 4, 2, 8, 5},
        {1, 0, 4, 8, 0, 0, 0, 3, 0},
        {0, 0, 8, 6, 3, 9, 7, 0, 0},
    //  ---------------------------
        {3, 8, 0, 4, 0, 0, 0, 2, 6},
        {6, 0, 0, 0, 8, 5, 1, 0, 3},
        {7, 0, 2, 0, 6, 3, 4, 0, 0},
    //  ---------------------------
        {0, 9, 0, 0, 4, 8, 5, 1, 0},
        {0, 3, 7, 5, 9, 0, 0, 0, 2},
        {8, 5, 0, 7, 0, 0, 0, 9, 4},
    };

    // std::cout << "input numbers (0 for blank):\n";
    // int input[9][9];
    // for(int i=0;i<9;i++) {
    //     for(int j=0;j<9;j++) {
    //         std::cin >> input[i][j];
    //     }
    // }

    // Board myBoard(input);
    Board myBoard(example);
    std::cout << "Given Board:\n";
    myBoard.printBoard();
    myBoard.solveBoard();
    std::cout << "\nSolution:\n";
    myBoard.printBoard();

    return 0;
}

/*
SUDOKU SOLVING METHODS:
visit: https://puzzling.stackexchange.com/questions/30519/techniques-to-solve-this-sudoku-puzzle/30540#30540
*/