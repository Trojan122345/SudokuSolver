//
// Created by Troja on 12/04/2024.
//

#ifndef SUDOKUSOLVER_CELL_H
#define SUDOKUSOLVER_CELL_H


#include <list>
#include "objects/numberGrid/TextBox.h"

class Cell
{
private:
    //If filled, this is the number
    //If not, finalNumber = 0
    int finalNumber;

    //# of marks
    int markedNumbers;

    //If cell is not filled, marks show all possible numbers
    bool marks[9];

    bool filled;
    TextBox *textBox;

    bool init;
public:
    Cell();
    ~Cell();

    [[nodiscard]] int getFinalNumber() const;
    void addTextBox(TextBox* cell);

    //Fills the final number
    void fill(int number);
    void fill(TextBox *cell);
    void fill();
    [[nodiscard]] bool isFilled() const;

    //Mark possible finalNumber
    void mark(int number);
    void removeMark(int number);
    bool checkMarkedNumber(int number);

    //Checks if cell has only one marked finalNumber
    //if so, fills the finalNumber and returns it
    //else returns 0
    int checkLoneNumber();

    std::string marksToString();

    void empty();
};


#endif //SUDOKUSOLVER_CELL_H
