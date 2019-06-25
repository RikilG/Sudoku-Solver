#include "Board.h"
#include<iostream>

#define DEBUG

int main() {
    
#ifdef DEBUG
    #include "Examples.h"
    Board myBoard(three_star);
#else
    // Take input from user.
    std::cout << "input numbers (0 for blank):\n";
    int input[9][9];
    for(int i=0;i<9;i++) {
        for(int j=0;j<9;j++) {
            std::cin >> input[i][j];
        }
    }
    Board myBoard(input);
#endif

    std::cout << "Given Board:\n";
    myBoard.printBoard();
    myBoard.solveBoard();
    std::cout << "\nSolution:\n";
    myBoard.printBoard();

#ifdef DEBUG
    int *ans = hidden_single_ans; //this is an array containing format { x, y, ans }
    if(myBoard.checkValue(ans[0], ans[1], ans[2])) {
        std::cout << ">>>PASS<<<\n";
    }
    else 
        std::cout << "!!! > FAIL: " << myBoard.grid[ ans[0] ][ ans[1] ].getValue() << "\n";
#endif

    return 0;
}

/*
SUDOKU SOLVING METHODS:
visit: https://puzzling.stackexchange.com/questions/30519/techniques-to-solve-this-sudoku-puzzle/30540#30540
*/