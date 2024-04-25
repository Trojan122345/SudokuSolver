//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include "Solver.h"

Solver::Solver() : cells(9), rows(9), cols(9), boxes(9)
{
  initCells();
  initSets();
}

Solver::~Solver()
{
  for (int i = 0; i < 9; i++)
  {
    this->cells[i] = std::vector<Cell*>(9);
    for (int ii = 0; ii < 9; ii++)
    {
      delete this->cells[i][ii];
    }
  }
}

void Solver::initCells()
{
  for (int i = 0; i < 9; i++)
  {
    this->cells[i] = std::vector<Cell*>(9);
    for (int ii = 0; ii < 9; ii++)
    {
      this->cells[i][ii] = new Cell();
    }
  }
}

void Solver::initSets()
{
  for (int i = 0; i < 9; i++)
  {
    for (int ii = 0; ii < 9; ii++)
    {
      rows[i].addCell(cells[i][ii]);
      cols[ii].addCell(cells[i][ii]);
      boxes[(i / 3) * 3 + ii / 3].addCell(cells[i][ii]);
    }
  }
}

//Use pointer
void Solver::setSleep(bool doSleep)
{
  for (auto &row: cells)
  {
    for (auto &cell: row)
      cell->setSleep(doSleep);
  }
}

void Solver::updateChanges(bool updateMarks)
{
  for (int i = 0; i < 9; i++)
  {
    rows[i].updateChanges(updateMarks);
    cols[i].updateChanges(updateMarks);
    boxes[i].updateChanges(updateMarks);
  }
}

void Solver::solve(bool &pause, bool &done)
{
  for (auto &row: cells)
  {
    for (auto &cell: row)
      cell->setPause(pause);
  }
  bool doAdvanced;
  do
  {
    doAdvanced = false;
    bool repeat;
    do
    {
      repeat = false;
      repeat |= checkLoneMarks();
      repeat |= checkSetsMissingNumbers();
      repeat |= checkSetsSingleMarks();
    } while (repeat);
    for (int i = 0; i < 9; i++)
    {
      doAdvanced |= !boxes[i].isSolved();
    }
    if (doAdvanced)
    {
      doAdvanced = checkBoxSingleRowCols();
      doAdvanced |= checkLimitedCellMarks();
    }
  } while (doAdvanced);
  updateChanges(true);
  done = true;
}

void Solver::solveBrute(bool &pause, bool &done)
{
  for (auto &row: cells)
  {
    for (auto &cell: row)
      cell->setPause(pause);
  }
  updateChanges(false);
  solveBruteRecursion(0, 0);
  done = true;
}

bool Solver::solveBruteRecursion(int cellRowIndex, int cellColIndex)
{
  if(stop!= nullptr && *stop)
    return true;
  if (cells[cellRowIndex][cellColIndex]->isSolved())
  {
    if ((cellColIndex < 8 && solveBruteRecursion(cellRowIndex, cellColIndex + 1)) ||
        (cellColIndex >= 8 && cellRowIndex < 8 && solveBruteRecursion(cellRowIndex + 1, 0)) ||
        (cellColIndex >= 8 && cellRowIndex >= 8))
    {
      return true;
    }
  }
  else
  {
    for (int digit = 0; digit < 9; digit++)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (!rows[cellRowIndex].isDigitSolved(digit) && !cols[cellColIndex].isDigitSolved(digit) &&
          !boxes[cellRowIndex / 3 * 3 + cellColIndex / 3].isDigitSolved(digit))
      /*{
        if (digit >= 8)
        {
          return false;
        }
      }
      else*/
      {
        cells[cellRowIndex][cellColIndex]->solve(digit);
        rows[cellRowIndex].updateChanges(false);
        cols[cellColIndex].updateChanges(false);
        boxes[cellRowIndex / 3 * 3 + cellColIndex / 3].updateChanges(false);
        if ((cellColIndex < 8 && solveBruteRecursion(cellRowIndex, cellColIndex + 1)) ||
            (cellColIndex >= 8 && cellRowIndex < 8 && solveBruteRecursion(cellRowIndex + 1, 0)) ||
            (cellColIndex >= 8 && cellRowIndex >= 8))
        {
          return true;
        }
        cells[cellRowIndex][cellColIndex]->empty();
        rows[cellRowIndex].removeDigit(digit);
        cols[cellColIndex].removeDigit(digit);
        boxes[cellRowIndex / 3 * 3 + cellColIndex / 3].removeDigit(digit);
      }
    }
  }
  return false;
}

bool Solver::checkLoneMarks()
{
  bool filled = false;
  bool repeat;
  do
  {
    if(stop!= nullptr && *stop)
      return true;
    repeat = false;
    for (int i = 0; i < 9; i++)
    {
      for (int ii = 0; ii < 9; ii++)
      {
        if (cells[i][ii]->checkLoneMark() >= 0)
        {
          rows[i].updateChanges(true);
          cols[ii].updateChanges(true);
          boxes[i / 3 * 3 + ii / 3].updateChanges(true);
          repeat = true;
          filled = true;
        }
      }
    }
  } while (repeat);
  return filled;
}

bool Solver::checkSetsMissingNumbers()
{
  bool filled = false;
  bool repeat;
  do
  {
    if(stop!= nullptr && *stop)
      return true;
    repeat = false;
    //Rows check
    for (auto &row: rows)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (row.checkLastNumber())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges(true);

    //Cols check
    for (auto &col: cols)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (col.checkLastNumber())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges(true);

    //Boxes check
    for (auto &box: boxes)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (box.checkLastNumber())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges(true);
  } while (repeat);
  return filled;
}

bool Solver::checkSetsSingleMarks()
{
  bool filled = false;
  bool repeat;

  do
  {
    if(stop!= nullptr && *stop)
      return true;
    repeat = false;
    //Rows check
    for (auto &row: rows)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (row.checkOnlyMark())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges(true);

    //Cols check
    for (auto &col: cols)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (col.checkOnlyMark())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges(true);

    //Boxes check
    for (auto &box: boxes)
    {
      if(stop!= nullptr && *stop)
        return true;
      if (box.checkOnlyMark())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges(true);
  } while (repeat);
  return filled;
}

bool Solver::checkBoxSingleRowCols()
{
  bool altered = false;
  for (int box = 0; box < 9; box++)
  {
    for (int digit = 0; digit < 9; digit++)
    {
      if(stop!= nullptr && *stop)
        return true;
      int boxRow = -1;
      int boxCol = -1;
      if (boxes[box].checkSingleRowCol(boxRow, boxCol, digit))
      {
        if (boxRow >= 0)
        {
          for (int col = 0; col < 9; col++)
          {
            if (col / 3 != box % 3)
            {
              altered |= cells[boxRow + (box / 3) * 3][col]->removeMark(digit);
            }
          }
        }
        else if (boxCol >= 0)
        {
          for (int row = 0; row < 9; row++)
          {
            if (row / 3 != box / 3)
            {
              altered |= cells[row][boxCol + (box % 3) * 3]->removeMark(digit);
            }
          }
        }
      }
    }
  }
  return altered;
}

bool Solver::checkLimitedCellMarks()
{
  bool filled = false;
  //Rows check
  for (auto &row: rows)
  {
    if(stop!= nullptr && *stop)
      return true;
    filled |= row.checkLimitedMarks();
  }

  //Cols check
  for (auto &col: cols)
  {
    if(stop!= nullptr && *stop)
      return true;
    filled |= col.checkLimitedMarks();
  }

  //Boxes check
  for (auto &box: boxes)
  {
    if(stop!= nullptr && *stop)
      return true;
    filled |= box.checkLimitedMarks();
  }
  return filled;
}

void Solver::empty()
{
  for (int i = 0; i < 9; i++)
  {
    for (int ii = 0; ii < 9; ii++)
    {
      cells[i][ii]->empty();
    }
    rows[i].reset();
    cols[i].reset();
    boxes[i].reset();
  }
}

bool Solver::checkSolvedPuzzle()
{
  for (int i = 0; i < 9; i++)
  {
    if (!boxes[i].isSolved() || !cols[i].isSolved() || !rows[i].isSolved() ||
        boxes[i].checkForConflicts() || cols[i].checkForConflicts() || rows[i].checkForConflicts())
      return false;
  }
  return true;
}

Cell* Solver::getCell(int row, int col)
{
  return cells[row][col];
}

void Solver::setStop(bool &stopExt)
{
  stop = &stopExt;
}
