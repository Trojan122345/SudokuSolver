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

    //Removes value from marks of all cells
    void removeMark(int number);
    bool limitedMarksRecursion(int finalDepth, int currentDepth, int startCell, bool boolArray[9]);
    bool limitedMarksRecursionStart(int finalDepth);
public:
    NineSet();
    ~NineSet();

    void addCell(Cell* c);//T
    void solveCell(int cellNumber, int digit);//T

    //If solvedDigits = 8, method solves the last digit and returns true
    bool checkLastNumber();//T

    //If a digit has only a single insertMark among cells of the set, solves the digit and returns true
    bool checkOnlyMark();//T

    //Checks if a digit is only in a single row or column of a box
    //If it is, returns true and corresponding row/col value
    //Works only for boxes
    bool checkSingleRowCol(int &boxRowReturn, int &boxColReturn, int digit);//T

    //Check if OR of marks across X cells has X marks
    //If yes, remove these marks from other cells in the set
    bool checkLimitedMarks();//T

    //Check for conflicting numbers - returns true if conflict is present
    bool checkForConflicts();

    //Check for any changes made to cells by other instances
    void updateChanges(bool updateMarks);//T
    void removeDigit(int digit);//T
    void reset();

    [[nodiscard]] bool isSolved() const;//T
    bool isDigitSolved(int digit);
};


#endif //SUDOKUSOLVER_NINESET_H
