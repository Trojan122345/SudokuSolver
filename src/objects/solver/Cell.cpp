//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include "objects/solver/Cell.h"

Cell::Cell() : marks{}, textBox(nullptr)
{
  finalNumber = -1;
  filled = false;
  for (bool &mark: marks)
  {
    mark = true;
  }
  markedNumbers = 9;
}

Cell::~Cell()
{

}

void Cell::addTextBox(TextBox *cell)
{
  this->textBox = cell;
}

void Cell::fill(int number)
{
  this->finalNumber = number;
  filled = true;
  for (bool &mark: marks)
  {
    mark = false;
  }
  markedNumbers = 0;
  if (textBox != nullptr)
    textBox->setText(std::to_string(finalNumber + 1));
}

void Cell::fill(TextBox *cell)
{
  this->textBox = cell;
  int number = textBox->getNumberFromText() - 1;
  if (number != -1)
  {
    fill(number);
  }
}

void Cell::fill()
{
  if (this->textBox != nullptr)
  {
    int number = textBox->getNumberFromText() - 1;
    if (number != -1)
    {
      fill(number);
    }
  }
}

int Cell::getFinalNumber() const
{
  return finalNumber;
}

bool Cell::isFilled() const
{
  return filled;
}

void Cell::mark(int number)
{
  bool isMarked = false;
  for (auto markedNumber: marks)
  {
    if (markedNumber)
    {
      isMarked = true;
      break;
    }
  }
  if (!isMarked)
  {
    marks[number] = true;
    markedNumbers++;
  }
}

void Cell::removeMark(int number)
{
  if (marks[number])
  {
    marks[number] = false;
    markedNumbers--;
  }
}

bool Cell::checkMarkedNumber(int number)
{
  return marks[number];
}

int Cell::checkLoneNumber()
{
  if (markedNumbers == 1)
  {
    for (int i = 0; i < 9; i++)
    {
      if (marks[i])
      {
        fill(i);
        return i;
      }
    }
  }

  return 0;
}

void Cell::empty()
{
  finalNumber = -1;
  filled = false;
  for (bool &mark: marks)
  {
    mark = true;
  }
  markedNumbers = 9;
}

std::string Cell::marksToString()
{
  std::string ret = "";

  for (int i = 0; i < 9; i++)
  {
    if(marks[i])
      ret += std::to_string(i) + " ";
  }

  return ret + "\n";
}