#include "Cell.h"
#include <vector>

bool Cell::hasValue() {
    if(value == 0)
        return false;
    return true;
}

int Cell::getValue() {
    return value;
}

void Cell::setValue(int value) {
    this->value = value;
    if(value == 0)
        return;
    for(int i=0;i<10;i++)
        options[i] = 0;
    options[value] = 1;
    optionsLeft = 1;
}

// Remove an option from the list of numbers (1-9)
int Cell::strikeOption(int number) {
    if(number>9)
        return False;
    else if(optionsLeft == 1)   // the cell contains only one number left which is the value of the cell
        return False;
    
    if(options[number] != 0) {
        optionsLeft -= 1;
        options[number] = 0;
        if(optionsLeft == 1) {      // we have only one option left. so find the option and set it as value
            for(int i=1;i<10;i++) { // array indices run from 1 to 9
                if(options[i] == 1) {
                    value = i;
                    return VALUE_SET;
                }
            }
        }
        return True;
    }
    return False;
}

std::vector<int> Cell::getOptions() {
    std::vector<int> posNumbers;
    for(int i=1;i<10;i++) {
        if(options[i] == 1)
            posNumbers.push_back(i);
    }
    return posNumbers;
}