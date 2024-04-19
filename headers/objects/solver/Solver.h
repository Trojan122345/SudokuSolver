//
// Created by Troja on 12/04/2024.
//

#ifndef SUDOKUSOLVER_SOLVER_H
#define SUDOKUSOLVER_SOLVER_H


#include <vector>
#include "Cell.h"
#include "NineSet.h"

class Solver
{
private:
    std::vector<std::vector<Cell*>> cells;
    std::vector<NineSet> rows, cols, boxes;
    bool *doPause;

    void updateChanges();

    //Checks for cells that have only one insertMark
    //If such cell is found, it fills in the digit
    bool checkLoneMarks();

    //Checks for sets with last missing digit
    //if such set is found, it fills in the digit
    bool checkSetsMissingNumbers();

    //Checks for digit that have only one insertMark in a set
    //If such digit is found, it fills it in
    bool checkSetsSingleMarks();

    //Checks if a digit has marks only in one row a col of a box
    //If such digit is found, that digit's marks from said row a col are removed from the other two boxes
    bool checkBoxSingleRowCols();

    //Checks if X cells of a set have only X digits marked
    //If found, removes the marks of said digits from the rest of the set
    bool checkLimitedCellMarks();
public:
    Solver();
    ~Solver();

    void initCells();
    void initSets();

    void addTextBoxes(std::vector<std::vector<TextBox*>> grid);
    void loadNumbers();

    void solve(bool &pause, bool &done);
    bool checkConflicts();


    void empty();
};


#endif //SUDOKUSOLVER_SOLVER_H
