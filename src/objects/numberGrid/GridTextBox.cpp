//
// Created by Troja on 20/04/2024.
//

#include <iostream>
#include "objects/numberGrid/GridTextBox.h"

GridTextBox::GridTextBox() : TextBox(), originalDigit(false), marks()
{
  cell = nullptr;
  initMarkText();
  for (bool &m: marks)
  {
    m = false;
  }
  solving = nullptr;
}

void GridTextBox::initMarkText()
{
  this->mark.setFont(fontArial);
  this->mark.setFillColor(sf::Color::Black);
  this->mark.setCharacterSize(9);
}

void GridTextBox::render(sf::RenderTarget* target)
{
  TextBox::render(target);
  for (int i = 0; i < 9; i++)
  {
    if (this->marks[i])
    {
      this->mark.setString(std::to_string(i + 1));
      setMarkPosition(i);
      target->draw(mark);
    }
  }
}

void GridTextBox::update()
{
  TextBox::update();
  if (solving != nullptr && *solving)
  {
    if (cell->getFinalNumber() >= 0)
    {
      deleteMarks();
      this->setText(std::to_string(cell->getFinalNumber() + 1));
    }
    else
    {
      this->setText("");
      for (int i = 0; i < 9; ++i)
      {
        setMark(i, cell->isDigitMarked(i));
      }
    }
  }
}

void GridTextBox::setMark(int digit, bool isSet)
{
  marks[digit] = isSet;
}

void GridTextBox::deleteMarks()
{
  for (auto &m: marks)
  {
    m = false;
  }
}

void GridTextBox::setOriginalDigit(bool isOriginal)
{
  originalDigit = isOriginal;
  if (isOriginal)
    this->setBackgroundColor(sf::Color(100, 220, 255, 50));
  else
    this->setBackgroundColor(sf::Color::Transparent);
}

void GridTextBox::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  bool temp = false;
  if (!isInBoundaries(mouseMoveEvent.x, mouseMoveEvent.y) && mouseIn && originalDigit)
  {
    temp = true;
  }
  TextBox::onMouseMove(mouseMoveEvent);
  if (temp)
    setBackgroundColor(sf::Color(100, 220, 255, 50));
}

void GridTextBox::setMarkPosition(int digit)
{
  mark.setOrigin(mark.getLocalBounds().width / 2, mark.getLocalBounds().height / 2);
  mark.setPosition(position.x + size.x / 4 * (digit % 3 * 1.25f + 0.75f),
                   position.y + -1 + this->size.y / 4 * (digit / 3 * 1.25f + 0.75f));
}

void GridTextBox::empty()
{
  setText("");
  deleteMarks();
  setOriginalDigit(false);
}

void GridTextBox::setCell(Cell* cellToSet)
{
  this->cell = cellToSet;
}

void GridTextBox::setSolving(bool* solvingToSet)
{
  this->solving = solvingToSet;
}

void GridTextBox::fillCell(bool doMarks)
{
  int digit = getNumberFromText() - 1;
  setOriginalDigit(digit > -1);
  if (doMarks || digit > -1)
    cell->solve(digit);
}
