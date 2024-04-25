//
// Created by Troja on 12/04/2024.
//

#include <thread>
#include "Cell.h"

Cell::Cell() : marks{}, pause(nullptr)
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
  pause = nullptr;
  delete pause;
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

    if (sleeping)
      sleep();

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
  if (!marks[digit])
  {
    marks[digit] = true;
    numberOfMarks++;
  }
  if (sleeping)
    sleep();
}

bool Cell::removeMark(int digit)
{
  bool ret = false;
  if (marks[digit])
  {
    ret = true;
    marks[digit] = false;
    numberOfMarks--;
  }
  if (sleeping)
    sleep();
  return ret;
}

bool Cell::isDigitMarked(int digit)
{
  return marks[digit];
}

bool* Cell::orMarks(const bool orMarks[9], int &ors)
{
  bool* ret = new bool[9];
  if (this->isSolved())
  {
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
  finalDigit = -1;
  solved = false;
  pause = nullptr;
  for (int i = 0; i < 9; i++)
  {
    removeMark(i);
  }
}

void Cell::sleep()
{
  using namespace std::chrono_literals;
  if (pause != nullptr)
  {
    while (*pause)
    {
      std::this_thread::sleep_for(10ms);
    }
  }
  std::this_thread::sleep_for(1ms);
}

void Cell::setSleep(bool doSleep)
{
  sleeping = doSleep;
}

void Cell::setPause(bool &pauseExt)
{
  pause = &pauseExt;
}
