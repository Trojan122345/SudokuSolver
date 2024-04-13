//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include "objects/solver/NineSet.h"

NineSet::NineSet() : numbers{}
{
  finished = false;
  filledNumbers = 0;
  for (auto &number: numbers)
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

void NineSet::addCell(Cell *c)
{
  cells.push_back(c);
}

bool NineSet::checkLastNumber()
{
  if (filledNumbers == 8)
  {
    //Find the missing number
    for(int i = 0; i < 9; i++)
    {
      if (!numbers[i])
      {
        //Find the empty cell
        for (auto &cell: cells)
        {
          if (!cell->isFilled())
          {
            //Fill the empty cell with the missing number
            cell->fill(i);
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool NineSet::checkOnlyMark()
{
  bool filled = false;
  bool repeat;

  if (filledNumbers < 8)
  {
    do
    {
      //repeat each time a number is filled - new possible single mark can be created
      repeat = false;
      for(int i = 0;i<9;i++)
      {
        //Find unfilled numbers
        if (!numbers[i])
        {
          int numberOfMarks = 0;
          Cell *tempCell;
          for (auto &cell: cells)
          {
            //Count cells in which number is marked
            if (!cell->isFilled() && cell->checkMarkedNumber(i))
            {
              numberOfMarks++;
              tempCell = cell;
            }
          }
          //Check for single mark, if true, fills number
          if (numberOfMarks == 1)
          {
            tempCell->fill(i);
            filled = true;
            repeat = true;
            tempCell = nullptr;
          }
        }
      }
    }while(repeat);
  }
  else if (filledNumbers == 8)
  {
    return checkLastNumber();
  }
  else if (filledNumbers == 9)
  {
    return false;
  }

  return filled;
}

void NineSet::updateChanges()
{
  for (auto &cell: cells)
  {
    if (cell->isFilled() && !numbers[cell->getFinalNumber()])
    {
      numbers[cell->getFinalNumber()] = true;
      filledNumbers++;
      removeMark(cell->getFinalNumber());
    }
  }
}

void NineSet::reset()
{
  finished = false;
  filledNumbers = 0;
  for (auto &number: numbers)
    number = false;
}

bool NineSet::isFinished() const
{
  return finished;
}

std::string NineSet::toString()
{
  std::string ret = "Set numbers:\n";
  for(int i = 0; i < 9; i++){
    if(numbers[i])
      ret += std::to_string(i) + " ";
  }

  ret += "\n\n";
  for(int i = 0; i < 9; i++){
    ret += "Cell " + std::to_string(i) + ": " + cells[i]->marksToString();
  }

  return ret + "\n";
}


