//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include <regex>
#include "objects/numberGrid/NumberGrid.h"

NumberGrid::NumberGrid() : boxes(9)
{
  initBorder(350, 150);
  initGrid();
  this->highlightedBox = nullptr;
}

NumberGrid::~NumberGrid()
{

}

void NumberGrid::initBorder(float posX, float posY)
{
  this->border.setFillColor(sf::Color::White);
  this->border.setSize(sf::Vector2f(31 * 9 + 1, 31 * 9 + 1));
  this->border.setScale(sf::Vector2f(1, 1));
  this->border.setOutlineThickness(3);
  this->border.setOutlineColor(sf::Color::Black);
  this->border.setPosition(posX, posY);
  this->position.x = posX;
  this->position.y = posY;
}

void NumberGrid::initGrid()
{
  float posX, posY = 0;
  for (int i = 0; i < 9; i++)
  {
    boxes[i] = std::vector<TextBox>(9);
    for (int ii = 0; ii < 9; ii++)
    {
      posX = this->position.x + 31.0f * (float) ii + (float) (ii / 3);

      posY = this->position.y + 31.0f * (float) i + (float) (i / 3);

      boxes[i][ii].setPosition(posX, posY);
    }
  }

}

void NumberGrid::render(sf::RenderTarget *target)
{
  target->draw(border);

  for (const auto &row: boxes)
  {
    for (auto box: row)
    {
      box.render(target);
    }
  }
}

void NumberGrid::update()
{

}

bool NumberGrid::isInBoundaries(float posX, float posY)
{
  return posX > border.getPosition().x && posX < border.getPosition().x + border.getSize().x &&
         posY > border.getPosition().y && posY < border.getPosition().y + border.getSize().y;
}

void NumberGrid::click(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  bool br = false;

  for (int i = 0; i < 9; i++)
  {
    for (int ii = 0; ii < 9; ii++)
    {
      if (boxes[i][ii].isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y))
      {
        if (this->highlightedBox != nullptr)
          this->highlightedBox->setHighlight(false);

        if (this->highlightedBox != &boxes[i][ii])
        {
          this->highlightedBox = &boxes[i][ii];
          this->highlightedBox->setHighlight();
        }
        else
        {
          this->highlightedBox = nullptr;
        }

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

void NumberGrid::textErased(){
  if(this->highlightedBox != nullptr){
    this->highlightedBox->setText("");
  }
}
