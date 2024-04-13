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
  for (bool &m: marks)
  {
    m = false;
  }
}

TextBox::~TextBox()
{

}

void TextBox::render(sf::RenderTarget *target)
{
  target->draw(box);
  target->draw(text);
  for (int i = 0; i < 9; i++)
  {
    if (this->marks[i])
    {
      this->mark.setString(std::to_string(i + 1));
      setTextPosition(mark, this->position.x + this->size.x / 4 * (i % 3 * 1.25f + 0.75f),
                      this->position.y - 1 + this->size.y / 4 * (i / 3 * 1.25f + 0.75f));
      target->draw(mark);
    }
  }
}

void TextBox::update()
{

}

void TextBox::initText()
{
  this->text.setCharacterSize(20);
  this->text.setFillColor(sf::Color::Black);
  this->text.setFont(font);

  this->mark.setFont(font);
  this->mark.setFillColor(sf::Color::Black);
  this->mark.setCharacterSize(9);
}

void TextBox::initBox()
{
  this->size.x = 30;
  this->size.y = 30;
  this->box.setSize(sf::Vector2f(30, 30));
  this->box.setFillColor(sf::Color::Transparent);
  this->box.setOutlineThickness(1);
  this->box.setOutlineColor(sf::Color::Black);
}

void TextBox::setText(std::string txt)
{
  this->text.setString(txt);
  setTextPosition(text, position.x + size.x / 2, position.y-5 + size.y / 2);
}

void TextBox::setString(sf::String str)
{
  this->text.setString(str);
  setTextPosition(text, position.x + size.x / 2, position.y-5 + size.y / 2);
}

void TextBox::setPosition(float posX, float posY)
{
  this->position.x = posX;
  this->position.y = posY;
  this->box.setPosition(posX, posY);
  setTextPosition(text, posX + size.x / 2, posY + size.y / 2);
}

void TextBox::setTextPosition(sf::Text &txt, float posX, float posY)
{
  txt.setOrigin(txt.getLocalBounds().width / 2, txt.getLocalBounds().height / 2);
  txt.setPosition(posX, posY);
}

sf::Font TextBox::getFont()
{
  sf::Font temp;

  //This should be handled differently - project is small, std::cout is enough for now
  if (!temp.loadFromFile("../res/fonts/arial.ttf"))
  {
    std::cout << "Failed to load font\n";
  }
  return temp;
}

//Sets size of the gridBorder - method actually creates scale based on the initial size which is then applied
//    this is necessary for correct text sizing and placement
void TextBox::setSize(float boxSize)
{
  this->scale = boxSize / 30;

  this->box.setSize(sf::Vector2f(boxSize, boxSize));
  this->text.setCharacterSize(20 * this->scale);

  this->setPosition(position.x, position.y);
}

void TextBox::setBackgroundColor(sf::Color c)
{
  this->box.setFillColor(c);
}

void TextBox::setMark(int digit, bool isSet)
{
  marks[digit] = isSet;
}

void TextBox::deleteMarks()
{
  for(auto &m : marks){
    m = false;
  }
}

bool TextBox::isInBoundaries(float posX, float posY)
{
  return posX >= position.x && posX <= position.x + 30 * scale && posY > position.y && posY <= position.y + 30 * scale;
}

void TextBox::setHighlight(bool isHighlighted)
{
  this->highlighted = isHighlighted;
  if (isHighlighted)
  {
    this->box.setOutlineColor(sf::Color(0, 150, 255));
    this->box.setOutlineThickness(3);
  }
  else
  {
    this->box.setOutlineColor(sf::Color::Black);
    this->box.setOutlineThickness(1);
  }
}

void TextBox::setHighlight()
{
  this->setHighlight(!this->highlighted);
}

void TextBox::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  if (isInBoundaries(mouseMoveEvent.x, mouseMoveEvent.y))
  {
    if (!this->mouseIn)
    {
      this->mouseIn = true;
      this->box.setFillColor(sf::Color(200, 200, 200, 70));
    }
  }
  else if (this->mouseIn)
  {
    this->mouseIn = false;
    this->box.setFillColor(sf::Color::Transparent);
  }
}

int TextBox::getNumberFromText()
{
  std::string retStr = this->text.getString().toAnsiString();
  if (retStr.empty())
    retStr = "0 ";
  return std::stoi(retStr);
}






