#include "Cell.h"

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
}

// Remove an option from the list of numbers (1-9)
bool Cell::strikeOption(int number) {
    if(number>9)
        return false;
    else if(optionsLeft == 1)   // the cell contains only one number left which is the value of the cell
        return false;
    options[number] = 0;
    optionsLeft -= 1;
    if(optionsLeft == 1) {      // we have only one option left. so find the option and set it as value
        for(int i=1;i<10;i++) { // array indices run from 1 to 9
            if(options[i] == 1) {
                value = i;
                break;
            }
        }
    }
    return true;
}