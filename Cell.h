#ifndef CELL_H
#define CELL_H

class Cell{
    private:
    int value;
    int options[10] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    int optionsLeft = 9;

    public:
    Cell(int value=0) {
        this->value = value;
        if(value != 0)
            optionsLeft = 1;
    }

    bool hasValue();
    int getValue();
    void setValue(int value);
    bool strikeOption(int number);

};

#endif