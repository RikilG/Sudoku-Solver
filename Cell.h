#ifndef CELL_H
#define CELL_H

#include <vector>

enum constants {
    False,
    True,
    VALUE_SET,
};

class Cell{
    private:
    int value;
    int options[10] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int optionsLeft = 9;

    public:
    Cell(int value=0) {
        this->value = value;
        if(value != 0) {
            optionsLeft = 1;
        }
    }
    bool hasValue();
    int getValue();
    void setValue(int value);
    void setOptions(std::vector<int>& cellOptions);
    std::vector<int> getOptions();
    int strikeOption(int number);

};

#endif