//
// Created by Troja on 12/04/2024.
//

#ifndef SUDOKUSOLVER_CELL_H
#define SUDOKUSOLVER_CELL_H


#include <list>

class Cell
{
private:
    //If solved, this is the digit
    //If not, finalDigit = -1
    int finalDigit;

    //# of marks
    int numberOfMarks;

    //If cell is not solved, marks show all possible digits
    bool marks[9];

    bool solved;

    bool sleeping;
    bool *pause;

    void sleep();
public:
    Cell();
    ~Cell();

    [[nodiscard]] int getFinalNumber() const;

    //Fills the final digit
    void solve(int number);
    [[nodiscard]] bool isSolved() const;

    //Mark (possible digit in the cell) manipulation
    void insertMark(int digit);
    bool removeMark(int digit);//Returns true if the mark has been removed
    bool isDigitMarked(int digit);

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

    void setSleep(bool doSleep);
    void setPause(bool &pauseExt);
};


#endif //SUDOKUSOLVER_CELL_H
