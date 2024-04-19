//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include "objects/solver/NineSet.h"

NineSet::NineSet() : digits{}
{
  solved = false;
  solvedDigits = 0;
  for (auto &number: digits)
    number = false;
}

NineSet::~NineSet()
{
  for (int i = 0; i < 9; i++)
  {
    cells[i] = nullptr;
  }
}

void NineSet::removeMark(int number)
{
  for (auto &cell: cells)
  {
    cell->removeMark(number);
  }
}

void NineSet::addCell(Cell* c)
{
  cells.push_back(c);
}

void NineSet::solveCell(int cellNumber, int digit)
{
  this->cells[cellNumber]->solve(digit);
  if (digit >= 0)
    digits[digit] = true;
  solvedDigits++;
  if (solvedDigits == 9)
    solved = true;
}

//Check the last missing digit of a set
//If the set has 8 digits solved, this method finds the last missing digit and writes it into the last empty cell
bool NineSet::checkLastNumber()
{
  if (solvedDigits == 8)
  {
    //Find the missing number
    for (int digit = 0; digit < 9; digit++)
    {
      if (!digits[digit])
      {
        //Find the empty cell
        for (int cellIndex = 0; cellIndex < 9; cellIndex++)
        {
          if (!cells[cellIndex]->isSolved())
          {
            //Solve the empty cell with the missing number
            solveCell(cellIndex, digit);
            return true;
          }
        }
      }
    }
  }
  return false;
}

//Check for digits that have only one possible position (insertMark) in a set
//If there's such a digit, method will write it into the corresponding cell
//If there's 8 solved digits, method will call the NineSet::checkLastNumber()
bool NineSet::checkOnlyMark()
{
  bool updated = false;

  if (solvedDigits < 8)
  {
    for (int digit = 0; digit < 9; digit++)
    {
      //Find unsolved digits
      if (!digits[digit])
      {
        int numberOfMarks = 0;
        int tempCellIndex = -1;
        for (int cellIndex = 0; cellIndex < 9; cellIndex++)
        {
          //Count cells in which number is marked
          if (!cells[cellIndex]->isSolved() && cells[cellIndex]->checkMarkedNumber(digit))
          {
            numberOfMarks++;
            tempCellIndex = cellIndex;
          }
        }
        //Check for single insertMark, if true, solves number
        if (numberOfMarks == 1)
        {
          solveCell(tempCellIndex, digit);
          updated = true;
        }
      }
    }
  }
  else if (solvedDigits == 8)
  {
    return checkLastNumber();
  }
  else if (solvedDigits == 9)
  {
    return false;
  }

  return updated;
}

bool NineSet::checkSingleRowCol(int &boxRowReturn, int &boxColReturn, int digit)
{
  int rowCount = 0, colCount = 0;
  boxRowReturn = -1;
  boxColReturn = -1;
  for (int cellsIndex = 0; cellsIndex < 9; cellsIndex++)
  {
    if (cells[cellsIndex]->checkMarkedNumber(digit))
    {
      if (boxRowReturn != cellsIndex / 3)
      {
        rowCount++;
        boxRowReturn = cellsIndex / 3;
      }
      if (boxColReturn != cellsIndex % 3)
      {
        colCount++;
        boxColReturn = cellsIndex % 3;
      }
    }
  }
  if (rowCount == 1)
  {
    boxColReturn = -1;
    return true;
  }
  if (colCount == 1)
  {
    boxRowReturn = -1;
    return true;
  }
  return false;
}

bool NineSet::checkLimitedMarks()
{
  if (solved)
    return false;
  return limitedMarksRecursion(9 - solvedDigits);
}

bool NineSet::limitedMarksRecursion(int finalDepth)
{
  bool ret = false;
  for (int cell = 0; cell < 9; ++cell)
  {
    bool boolArray[9];
    if (!cells[cell]->isSolved())
    {
      for (int digit = 0; digit < 9; ++digit)
      {
        boolArray[digit] = cells[cell]->checkMarkedNumber(digit);
      }
      ret |= limitedMarksRecursion(finalDepth, 2, cell + 1, boolArray);
    }
  }

  return ret;
}

bool NineSet::limitedMarksRecursion(int finalDepth, int currentDepth, int startCell, bool boolArray[9])
{
  if (finalDepth < currentDepth)
  {
    return false;
  }
  bool ret = false;

  bool orResults[9][9];

  int totalMarks[9];
  for (int comparedCell = startCell; comparedCell < 9; comparedCell++)
  {
    if (cells[comparedCell]->isSolved())
    {
      continue;
    }
    bool* tempResult = cells[comparedCell]->orMarks(boolArray, totalMarks[comparedCell]);
    for (int i = 0; i < 9; i++)
      orResults[comparedCell][i] = tempResult[i];
  }
  for (int comparedCell = startCell; comparedCell < 9; comparedCell++)
  {
    if (cells[comparedCell]->isSolved())
    {
      continue;
    }
    if (totalMarks[comparedCell] == currentDepth)
    {
      for (auto &cell: cells)
        ret |= cell->fixLimitedMarks(orResults[comparedCell]);

    }
    else
      ret |= limitedMarksRecursion(finalDepth, currentDepth + 1, comparedCell + 1, orResults[comparedCell]);
  }

  return ret;
}

bool NineSet::checkForConflicts()
{
  bool tempDigits[9];
  for (bool & tempDigit : tempDigits)
  {
    tempDigit = false;
  }
  for (int i = 0; i < 9; i++)
  {
    if (cells[i]->isSolved())
    {
      if (!tempDigits[cells[i]->getFinalNumber()])
        tempDigits[cells[i]->getFinalNumber()] = true;
      else
        return true;
    }
  }
  return false;
}

void NineSet::updateChanges()
{
  for (auto &cell: cells)
  {
    if (cell->isSolved() && !digits[cell->getFinalNumber()])
    {
      digits[cell->getFinalNumber()] = true;
      solvedDigits++;
      if (solvedDigits == 9)
        solved = true;
      removeMark(cell->getFinalNumber());
    }
  }
}

void NineSet::reset()
{
  solved = false;
  solvedDigits = 0;
  for (auto &number: digits)
    number = false;
}

bool NineSet::isSolved() const
{
  return solved;
}


