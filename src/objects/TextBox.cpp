//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include "TextBox.h"
#include "enums.h"

sf::Font TextBox::fontArial = *TextBox::getFont(FontType::ARIAL);

TextBox::TextBox()
{
  this->scale = 1;
  this->highlighted = false;

  initText();
  initBox();
}

TextBox::~TextBox()
{

}

void TextBox::render(sf::RenderTarget* target)
{
  target->draw(box);
  target->draw(text);
}

void TextBox::update()
{
  Object::update();
}

void TextBox::initText()
{
  this->text.setCharacterSize(20);
  this->text.setFillColor(sf::Color::Black);
  this->text.setFont(fontArial);
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

void TextBox::setText(const std::string &txt)
{
  this->text.setString(txt);
  setTextPosition();
}

void TextBox::setString(const sf::String &str)
{
  this->text.setString(str);
  setTextPosition();
}

void TextBox::setPosition(float posX, float posY)
{
  this->position.x = posX;
  this->position.y = posY;
  this->box.setPosition(posX, posY);
  setTextPosition();
}

void TextBox::setTextPosition()
{
  text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
  text.setPosition(position.x + size.x / 2, position.y - 5 + size.y / 2);
}

sf::Font* TextBox::getFont(FontType fontType)
{
  auto* temp = new sf::Font();

  //This should be handled differently - project is small, std::cout is enough for now
  if (!temp->loadFromFile(getFontPath[fontType]))
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
  if (locked == nullptr || !*locked)
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
}

int TextBox::getNumberFromText()
{
  std::string retStr = this->text.getString().toAnsiString();
  if (retStr.empty())
    retStr = "0 ";
  return std::stoi(retStr);
}

void TextBox::onLock()
{
  this->box.setFillColor(sf::Color(150, 150, 150, 55));
  setHighlight(false);
}

void TextBox::onUnLock()
{
  this->box.setFillColor(sf::Color::Transparent);
}






