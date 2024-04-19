//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include <thread>
#include "objects/solver/Cell.h"

Cell::Cell() : marks{}, textBox(nullptr)
{
  finalDigit = -1;
  solved = false;
  for (bool &mark: marks)
  {
    mark = false;
  }
  numberOfMarks = 0;
  sleeping = false;
}

Cell::~Cell()
{
  textBox = nullptr;
}

void Cell::addTextBox(TextBox* cell)
{
  this->textBox = cell;
}

void Cell::solve(int number)
{
  using namespace std::chrono_literals;
  if (number >= 0)
  {
    this->finalDigit = number;
    solved = true;
    for (int i = 0; i < 9; i++)
    {
      removeMark(i);
    }
    if (textBox != nullptr)
    {
      textBox->setText(std::to_string(finalDigit + 1));
      if (sleeping)
        sleep();
    }
  }
  else
  {
    finalDigit = -1;
    solved = false;
    for (int i = 0; i < 9; i++)
    {
      insertMark(i);
    }
  }
}

void Cell::fillFromTextBox()
{
  if (this->textBox != nullptr)
  {
    int number = textBox->getNumberFromText() - 1;
    solve(number);
    if (number != -1)
      textBox->setBackgroundColor(sf::Color(100, 220, 255, 50));
    sleeping = true;
  }
}

int Cell::getFinalNumber() const
{
  return finalDigit;
}

bool Cell::isSolved() const
{
  return solved;
}

void Cell::insertMark(int digit)
{
  using namespace std::chrono_literals;
  if (!marks[digit])
  {
    marks[digit] = true;
    if (textBox != nullptr)
      textBox->setMark(digit, true);
    numberOfMarks++;
  }
  if (sleeping)
    sleep();
}

bool Cell::removeMark(int digit)
{
  bool ret = false;
  using namespace std::chrono_literals;
  if (marks[digit])
  {
    ret = true;
    marks[digit] = false;
    if (textBox != nullptr)
      textBox->setMark(digit, false);
    numberOfMarks--;
  }
  if (sleeping)
    sleep();
  return ret;
}

bool Cell::checkMarkedNumber(int digit)
{
  return marks[digit];
}

bool* Cell::orMarks(Cell* cellToOr, int &ors)
{
  if(cellToOr->isSolved()){
    bool* ret = new bool[9];
    ors = 9;
    for (int i = 0; i < 9; i++)
    {
      ret[i] = true;
    }
    return ret;
  }
  return orMarks(cellToOr->marks, ors);
}

bool* Cell::orMarks(const bool orMarks[9], int &ors)
{
  bool* ret = new bool[9];
  if(this->isSolved()){
    ors = 9;
    for (int i = 0; i < 9; i++)
    {
      ret[i] = true;
    }
    return ret;
  }
  ors = 0;
  for (int i = 0; i < 9; i++)
  {
    ret[i] = marks[i] || orMarks[i];
    if (ret[i])
      ors++;
  }
  return ret;
}

bool Cell::fixLimitedMarks(const bool limitedMarks[9])
{
  if (solved)
    return false;
  bool different = false;
  bool ret = false;
  for (int i = 0; i < 9; i++)
  {
    if (!limitedMarks[i] && marks[i])
    {
      different = true;
      break;
    }
  }
  for (int i = 0; i < 9; i++)
  {
    if (different && limitedMarks[i])
    {
      ret |= removeMark(i);
    }
  }
  return ret;
}

int Cell::getNumberOfMarks() const
{
  return numberOfMarks;
}

int Cell::checkLoneMark()
{
  if (numberOfMarks == 1)
  {
    for (int i = 0; i < 9; i++)
    {
      if (marks[i])
      {
        solve(i);
        return i;
      }
    }
  }

  return -1;
}

void Cell::empty()
{
  sleeping = false;
  finalDigit = -1;
  solved = false;
  for (int i = 0; i < 9; i++)
  {
    removeMark(i);
  }
}

void Cell::sleep()
{
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1ms);
}
