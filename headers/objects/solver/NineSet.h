//
// Created by Troja on 12/04/2024.
//

#ifndef SUDOKUSOLVER_NINESET_H
#define SUDOKUSOLVER_NINESET_H


#include <vector>
#include "Cell.h"

class NineSet
{
private:
    std::vector<Cell*> cells;

    //# of already filled numbers
    int filledNumbers;

    //If number is filled, numbers[i] = true
    bool numbers[9];

    bool finished;

    //Removes number from marks of all cells
    void removeMark(int number);
public:
    NineSet();
    ~NineSet();

    void addCell(Cell* c);

    //If filledNumbers = 8, method fills the last number and returns true
    bool checkLastNumber();

    //Fills number if the number has only a single mark among cells of the set
    bool checkOnlyMark();

    //Other instances can alter the cells - this method will update the changes
    //This means:
    //    - cross-checks all filled cells with numbers[], if number[numberInCell]=true
    //    - if not, updates number and removes it from marks in all other cells

    bool checkSingleRowCol(int &boxRowReturn, int &boxColReturn, int digit);

    void updateChanges();
    void reset();

    [[nodiscard]] bool isFinished() const;

    //For debug
    std::string toString();
};


#endif //SUDOKUSOLVER_NINESET_H
