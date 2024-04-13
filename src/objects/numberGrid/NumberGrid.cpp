//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include <regex>
#include "objects/numberGrid/NumberGrid.h"

NumberGrid::NumberGrid(float posX, float posY) : cells(9)
{
  initBorder(posX, posY);
  initGrid();
  this->highlightedBox = nullptr;
}

NumberGrid::~NumberGrid()
{
  this->highlightedBox = nullptr;
  for (auto row: cells)
  {
    for (auto &col: row)
    {
      delete col;
    }
  }
}

void NumberGrid::initBorder(float posX, float posY)
{
  //Is it necessary?
  this->position.x = posX;
  this->position.y = posY;

  this->gridBorder.setFillColor(sf::Color::White);
  this->gridBorder.setSize(sf::Vector2f(31 * 9 + 1, 31 * 9 + 1));
  this->gridBorder.setScale(sf::Vector2f(1, 1));
  this->gridBorder.setOutlineThickness(3);
  this->gridBorder.setOutlineColor(sf::Color::Black);
  this->gridBorder.setPosition(position);
}

void NumberGrid::initGrid()
{
  float posX, posY;
  for (int i = 0; i < 9; i++)
  {
    this->cells[i] = std::vector<TextBox *>(9);
    for (int ii = 0; ii < 9; ii++)
    {
      posX = this->position.x + 31.0f * (float) ii + (float) (ii / 3);

      posY = this->position.y + 31.0f * (float) i + (float) (i / 3);

      this->cells[i][ii] = new TextBox();
      this->cells[i][ii]->setPosition(posX, posY);
    }
  }
}

void NumberGrid::render(sf::RenderTarget *target)
{
  target->draw(gridBorder);


  for (auto row: cells)
  {
    for (auto &box: row)
    {
      box->render(target);
    }
  }

  if (highlightedBox != nullptr)
    highlightedBox->render(target);
}

void NumberGrid::update()
{

}

bool NumberGrid::isInBoundaries(float posX, float posY)
{
  return posX > gridBorder.getPosition().x && posX < gridBorder.getPosition().x + gridBorder.getSize().x &&
         posY > gridBorder.getPosition().y && posY < gridBorder.getPosition().y + gridBorder.getSize().y;
}

void NumberGrid::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  bool br = false;


  for (auto row: cells)
  {
    for (auto &box: row)
    {
      if (box->isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y))
      {
        this->highlightBox(box);

        br = true;
        break;
      }
    }
    if (br)
      break;
  }
}

void NumberGrid::textEntered(const sf::String &str)
{
  std::string s = str.toAnsiString();
  std::regex reg("[1-9]");
  if (this->highlightedBox != nullptr && std::regex_match(s, reg))
    this->highlightedBox->setString(str);
}

void NumberGrid::textErased()
{
  if (this->highlightedBox != nullptr)
  {
    this->highlightedBox->setText("");
  }
}

void NumberGrid::movePressed(sf::Keyboard::Key keyPressed)
{
  if (this->highlightedBox != nullptr)
  {
    int boxPos = highlightedBox->getID() - this->cells[0][0]->getID();
    switch (keyPressed)
    {
      case sf::Keyboard::Left:
        if (boxPos % 9 == 0)
          boxPos += 8;
        else
          boxPos -= 1;
        break;
      case sf::Keyboard::Right:
        if (boxPos % 9 == 8)
          boxPos -= 8;
        else
          boxPos += 1;
        break;
      case sf::Keyboard::Up:
        if (boxPos < 9)
          boxPos += 9 * 8;
        else
          boxPos -= 9;
        break;
      case sf::Keyboard::Down:
        if (boxPos > 71)
          boxPos -= 9 * 8;
        else
          boxPos += 9;
        break;
      default:
        break;
    }
    highlightBox(cells[boxPos / 9][boxPos % 9]);
  }
}

void NumberGrid::highlightBox(TextBox *box)
{
  if (this->highlightedBox != nullptr)
    this->highlightedBox->setHighlight(false);

  if (this->highlightedBox == nullptr || !box->compare(this->highlightedBox))
  {
    this->highlightedBox = box;
    this->highlightedBox->setHighlight();
  }
  else
  {
    this->highlightedBox = nullptr;
  }
}

void NumberGrid::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  for (auto row: cells)
  {
    for (auto &box: row)
    {
      box->onMouseMove(mouseMoveEvent);
    }
  }
}

void NumberGrid::keyPressed(sf::Keyboard::Key key)
{
  switch (key)
  {
    case sf::Keyboard::Delete:
    case sf::Keyboard::BackSpace:
      this->textErased();
      break;
    case sf::Keyboard::Up:
    case sf::Keyboard::Down:
    case sf::Keyboard::Left:
    case sf::Keyboard::Right:
      this->movePressed(key);
      break;
    default:
      break;
  }
}

void NumberGrid::setText(const std::string& str, int cellRow, int cellCol)
{
  this->cells[cellRow][cellCol]->setText(str);
}

int **NumberGrid::getNumbers()
{
  int **ret = new int *[9];
  for (int i = 0; i < 9; i++)
  {
    ret[i] = new int[9];
    for (int ii = 0; ii < 9; ii++)
    {
      ret[i][ii] = cells[i][ii]->getNumberFromText();
    }
  }

  return ret;
}

void NumberGrid::deleteAllText()
{
  for(int i = 0; i < 9; i++){
    for(int ii = 0; ii < 9; ii ++){
      cells[i][ii]->setText("");
      cells[i][ii]->deleteMarks();
      cells[i][ii]->setBackgroundColor(sf::Color::Transparent);
    }
  }
}
