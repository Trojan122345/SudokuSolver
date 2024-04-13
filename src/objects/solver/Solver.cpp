//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include "objects/solver/Solver.h"

Solver::Solver() : cells(9), rows(9), cols(9), boxes(9)
{
  initCells();
  initSets();
}

Solver::~Solver()
{
  for (int i = 0; i < 9; i++)
  {
    this->cells[i] = std::vector<Cell *>(9);
    for (int ii = 0; ii < 9; ii++)
    {
      delete this->cells[i][ii];
      this->cells[i][ii] = nullptr;
    }
  }
}

void Solver::initCells()
{
  for (int i = 0; i < 9; i++)
  {
    this->cells[i] = std::vector<Cell *>(9);
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

void Solver::addTextBoxes(std::vector<std::vector<TextBox *>> grid)
{
  for (int i = 0; i < 9; i++)
  {
    for (int ii = 0; ii < 9; ii++)
    {
      this->cells[i][ii]->addTextBox(grid[i][ii]);
    }
  }
}

void Solver::loadNumbers(int **numbers)
{
  for (int i = 0; i < 9; i++)
  {
    for (int ii = 0; ii < 9; ii++)
    {
      if (numbers[i][ii] != 0)
        this->cells[i][ii]->fill(numbers[i][ii] - 1);
    }
  }

  updateChanges();
}

void Solver::loadNumbers(std::vector<std::vector<TextBox *>> grid)
{
  for (int i = 0; i < 9; i++)
  {
    for (int ii = 0; ii < 9; ii++)
    {
      this->cells[i][ii]->fill(grid[i][ii]);
    }
  }

  updateChanges();
}

void Solver::loadNumbers()
{
  for (auto &row: cells)
  {
    for (auto &cell: row)
    {
      cell->fill();
    }
  }

  updateChanges();
}

void Solver::updateChanges()
{
  for (int i = 0; i < 9; i++)
  {
    rows[i].updateChanges();
    cols[i].updateChanges();
    boxes[i].updateChanges();
  }
}

void Solver::solve()
{
  bool repeatTricks;
  do
  {
    repeatTricks = false;
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
      repeatTricks |= !boxes[i].isFinished();
    }
    if (repeatTricks)
    {
      repeatTricks = checkBoxSingleRowCols();
    }
  } while (repeatTricks);
}


bool Solver::checkLoneMarks()
{
  bool filled = false;
  bool repeat;
  do
  {
    repeat = false;
    for (int i = 0; i < 9; i++)
    {
      for (int ii = 0; ii < 9; ii++)
      {
        if (cells[i][ii]->checkLoneNumber() >= 0)
        {
          rows[i].updateChanges();
          cols[ii].updateChanges();
          boxes[i / 3 * 3 + ii / 3].updateChanges();
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
    repeat = false;
    //Rows check
    for (auto &row: rows)
    {
      if (row.checkLastNumber())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges();

    //Cols check
    for (auto &col: cols)
    {
      if (col.checkLastNumber())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges();

    //Boxes check
    for (auto &box: boxes)
    {
      if (box.checkLastNumber())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges();
  } while (repeat);
  return filled;
}

bool Solver::checkSetsSingleMarks()
{
  bool filled = false;
  bool repeat;

  do
  {
    repeat = false;
    //Rows check
    for (auto &row: rows)
    {
      if (row.checkOnlyMark())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges();

    //Cols check
    for (auto &col: cols)
    {
      if (col.checkOnlyMark())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges();

    //Boxes check
    for (auto &box: boxes)
    {
      if (box.checkOnlyMark())
      {
        repeat = true;
        filled = true;
      }
    }
    updateChanges();
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
