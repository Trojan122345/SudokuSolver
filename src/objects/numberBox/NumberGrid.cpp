//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include "objects/numberBox/NumberGrid.h"

NumberGrid::NumberGrid()
{
  initBox(50, 50);
}

NumberGrid::~NumberGrid()
{

}

void NumberGrid::initBox(float posX, float posY)
{
  this->box.setFillColor(sf::Color::White);
  this->box.setSize(sf::Vector2f(540, 540));
  this->box.setScale(sf::Vector2f(1, 1));
  this->box.setOutlineThickness(3);
  this->box.setOutlineColor(sf::Color::Black);
  this->box.setPosition(posX, posY);

  //temp
  isHighlighted = false;
}

void NumberGrid::render(sf::RenderTarget *target)
{
  target->draw(box);

  tbox.render(target);
}

void NumberGrid::update()
{

}

bool NumberGrid::isInBoundaries(float posX, float posY)
{
  return posX > box.getPosition().x && posX < box.getPosition().x + box.getSize().x &&
         posY > box.getPosition().y && posY < box.getPosition().y + box.getSize().y;
}

void NumberGrid::click(sf::Event::MouseButtonEvent mouseButtonEvent)
{
    if(tbox.isInBoundaries((float) mouseButtonEvent.x, (float) mouseButtonEvent.y)){
      isHighlighted = !isHighlighted;
      tbox.setHighlight(isHighlighted);
    }
}

void NumberGrid::textEntered(const sf::String& str)
{
  if(isHighlighted)
    this->tbox.setString(str);
}
