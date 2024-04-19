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
    //If solved, this is the digit
    //If not, finalDigit = 0
    int finalDigit;

    //# of marks
    int numberOfMarks;

    //If cell is not solved, marks show all possible digits
    bool marks[9];

    bool solved;
    TextBox* textBox;

    bool sleeping;
public:
    Cell();
    ~Cell();

    [[nodiscard]] int getFinalNumber() const;
    void addTextBox(TextBox* cell);

    //Fills the final digit
    void solve(int number);
    void fillFromTextBox();
    [[nodiscard]] bool isSolved() const;

    //Mark (possible digit in the cell) manipulation
    void insertMark(int digit);
    bool removeMark(int digit);
    bool checkMarkedNumber(int digit);

    //Compares marks of each cell
    //Returns number of different Marks
    bool* orMarks(Cell* cellToOr, int &ors);
    bool* orMarks(const bool marks[], int &ors);
    bool fixLimitedMarks(const bool limitedMarks[9]);

    //Checks if cell has only one marked digit
    //if so, fills the finalDigit and returns it
    //else returns -1
    int checkLoneMark();

    void empty();
    [[nodiscard]] int getNumberOfMarks() const;

    static void sleep();
};


#endif //SUDOKUSOLVER_CELL_H
