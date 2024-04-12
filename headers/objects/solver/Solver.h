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

    void updateChanges();

    bool checkLoneMarks();
    bool checkSetsMissingNumbers();
    bool checkSetsSingleMarks();
public:
    Solver();
    ~Solver();

    void initCells();
    void initSets();

    void addTextBoxes(std::vector<std::vector<TextBox*>> grid);
    void loadNumbers(int** numbers);
    void loadNumbers(std::vector<std::vector<TextBox*>> grid);
    void loadNumbers();
    void solve();


    void empty();
};


#endif //SUDOKUSOLVER_SOLVER_H
