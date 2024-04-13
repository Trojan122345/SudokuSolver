//
// Created by Troja on 12/04/2024.
//

#include <iostream>
#include <thread>
#include "objects/solver/Cell.h"

Cell::Cell() : marks{}, textBox(nullptr)
{
  finalNumber = -1;
  filled = false;
  for (bool &mark: marks)
  {
    mark = false;
  }
  markedNumbers = 0;
  init = false;
}

Cell::~Cell()
{
  textBox = nullptr;
}

void Cell::addTextBox(TextBox *cell)
{
  this->textBox = cell;
}

void Cell::fill(int number)
{
  using namespace std::chrono_literals;
  if (number >= 0)
  {
    this->finalNumber = number;
    filled = true;
    for (int i = 0; i < 9; i++)
    {
      removeMark(i);
    }
    if (textBox != nullptr)
    {
      textBox->setText(std::to_string(finalNumber + 1));
      if (init)
        std::this_thread::sleep_for(20ms);
    }
  }
  else
  {
    finalNumber = -1;
    filled = false;
    for (int i = 0; i < 9; i++)
    {
      mark(i);
    }
  }
}

void Cell::fill(TextBox *cell)
{
  this->textBox = cell;
  int number = textBox->getNumberFromText() - 1;
  fill(number);
}

void Cell::fill()
{
  if (this->textBox != nullptr)
  {
    int number = textBox->getNumberFromText() - 1;
    fill(number);
    if (number != -1)
      textBox->setBackgroundColor(sf::Color(100, 220, 255, 50));
    init = true;
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
  using namespace std::chrono_literals;
  if (!marks[number])
  {
    marks[number] = true;
    textBox->setMark(number, true);
    markedNumbers++;
  }
  if (init)
    std::this_thread::sleep_for(2ms);
}

bool Cell::removeMark(int number)
{
  bool ret = false;
  using namespace std::chrono_literals;
  if (marks[number])
  {
    ret = true;
    marks[number] = false;
    textBox->setMark(number, false);
    markedNumbers--;
  }
  if (init)
    std::this_thread::sleep_for(2ms);
  return ret;
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

  return -1;
}

void Cell::empty()
{
  finalNumber = -1;
  filled = false;
  for (int i = 0; i < 9; i++)
  {
    removeMark(i);
  }
  init = false;
}

std::string Cell::marksToString()
{
  std::string ret = "";

  for (int i = 0; i < 9; i++)
  {
    if (marks[i])
      ret += std::to_string(i) + " ";
  }

  return ret + "\n";
}
