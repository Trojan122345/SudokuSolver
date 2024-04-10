//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include "objects/numberGrid/TextBox.h"

sf::Font TextBox::font = TextBox::getFont();

TextBox::TextBox()
{
  this->scale = 1;
  this->highlighted = false;

  initText();
  initBox();
  setPosition(50, 50);
}

TextBox::~TextBox()
{

}

void TextBox::render(sf::RenderTarget *target)
{
  target->draw(box);
  target->draw(text);
}

void TextBox::update()
{

}

void TextBox::initText()
{
  this->text.setCharacterSize(20);
  this->text.setFillColor(sf::Color::Black);
  this->text.setFont(font);
}

void TextBox::initBox()
{
  this->box.setSize(sf::Vector2f(30, 30));
  this->box.setFillColor(sf::Color::Transparent);
  this->box.setOutlineThickness(1);
  this->box.setOutlineColor(sf::Color::Black);
}

void TextBox::setText(std::string txt)
{
  this->text.setString(txt);
}

void TextBox::setString(sf::String str)
{
  this->text.setString(str);
}

void TextBox::setPosition(float posX, float posY)
{
  this->position.x = posX;
  this->position.y = posY;
  this->text.setPosition(posX + 10 * this->scale, posY + 5 * this->scale);
  this->box.setPosition(posX, posY);
}

sf::Font TextBox::getFont()
{
  sf::Font temp;

  //This should be handled differently - project is small, cout is enough for now
  if (!temp.loadFromFile("../res/arial.ttf"))
  {
    std::cout << "Failed to load font\n";
  }
  return temp;
}

//Sets size of the border - method actually creates scale based on the initial size which is then applied
//    this is necessary for correct text sizing and placement
void TextBox::setSize(float boxSize)
{
  this->scale = boxSize / 30;

  this->box.setSize(sf::Vector2f(boxSize, boxSize));
  this->text.setCharacterSize(20 * this->scale);

  this->setPosition(position.x, position.y);
}

bool TextBox::isInBoundaries(float posX, float posY)
{
  return posX >= position.x && posX <= position.x + 30 * scale && posY > position.y && posY <= position.y + 30*scale;
}

void TextBox::setHighlight(bool isHighlighted)
{
  this->highlighted = isHighlighted;
  if(isHighlighted){
    this->box.setOutlineColor(sf::Color(0, 150, 255));
    this->box.setOutlineThickness(3);
  }
  else{
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setOutlineThickness(1);
  }
}

void TextBox::setHighlight()
{
  this->setHighlight(!this->highlighted);
}



