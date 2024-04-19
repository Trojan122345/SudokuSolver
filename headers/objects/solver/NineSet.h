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

    //# of already solved digits
    int solvedDigits;

    //If digit is solved, digits[i] = true
    bool digits[9];

    bool solved;

    //Removes number from marks of all cells
    void removeMark(int number);
    bool limitedMarksRecursion(int finalDepth, int currentDepth, int startCell, bool boolArray[9]);
    bool limitedMarksRecursion(int finalDepth);
public:
    NineSet();
    ~NineSet();

    void addCell(Cell* c);
    void solveCell(int cellNumber, int digit);

    //If solvedDigits = 8, method solves the last digit and returns true
    bool checkLastNumber();

    //If a digit has only a single insertMark among cells of the set, solves the digit and returns true
    bool checkOnlyMark();

    //Checks if a digit is only in a single row or column of a box
    //If it is, returns true and corresponding row/col number
    //Works only for boxes
    bool checkSingleRowCol(int &boxRowReturn, int &boxColReturn, int digit);

    //Check if OR of marks across X cells has X marks
    //If yes, remove these marks from other cells in the set
    bool checkLimitedMarks();

    //Check for conflicting numbers - returns true if conflict is present
    bool checkForConflicts();

    //Other instances can alter the cells - this method will update the changes
    //This means:
    //    - cross-checks all solved cells with digits[], whether digit[digitInCell]=true
    //    - if not, updates number and removes it from marks in all other cells
    void updateChanges();
    void reset();

    [[nodiscard]] bool isSolved() const;
};


#endif //SUDOKUSOLVER_NINESET_H
