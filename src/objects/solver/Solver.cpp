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
      this->cells[i][ii]->fill(grid[i][ii]);
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
  bool repeat;
  do
  {
    repeat = false;
    repeat |= checkLoneMarks();
    repeat |= checkSetsMissingNumbers();
    repeat |= checkSetsSingleMarks();
  } while (repeat);
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
