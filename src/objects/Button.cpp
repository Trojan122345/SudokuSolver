//
// Created by Troja on 11/04/2024.
//

#include <iostream>
#include <thread>
#include "objects/Button.h"
#include "objects/TextBox.h"

Button::Button()
{
  initButton(0, 0);
  initText();
}

Button::Button(float posX, float posY)
{
  initButton(posX, posY);
  initText();
}

Button::~Button()
{

}

void Button::loadTextureFromFile(std::string filename)
{
  this->texture.loadFromFile(filename);
}

void Button::initSprite(float posX, float posY, float sizeX, float sizeY)
{
  this->position.x = posX;
  this->position.y = posY;

  this->size.x = sizeX;
  this->size.y = sizeY;

  this->sprite.setTexture(this->texture);
  this->sprite.setPosition(position);
}

void Button::initButton(float posX, float posY)
{
  this->loadTextureFromFile("../res/buttons/button.png");
  this->initSprite(posX, posY, 150, 50);
}

void Button::initText()
{
  this->text.setFont(TextBox::fontArial);
  this->text.setCharacterSize(20);
  this->text.setString("Click me!");
  this->text.setFillColor(sf::Color::Black);

  adjustTextPosition();
}

void Button::adjustTextPosition()
{
  this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height / 2);
  this->text.setPosition(this->position.x + this->size.x / 2, this->position.y + this->size.y / 2);
}

void Button::render(sf::RenderTarget* target)
{
  target->draw(sprite);
  target->draw(text);
}

void Button::update()
{
  Object::update();
}

bool Button::isInBoundaries(float posX, float posY)
{
  return posX >= this->position.x && posX <= this->position.x + this->size.x &&
         posY >= this->position.y && posY <= this->position.y + this->size.y;
}

void Button::onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (this->isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y) && !this->mouseDown)
  {
    this->mouseDown = true;
    this->loadTextureFromFile("../res/buttons/buttonClick.png");
  }
}

void Button::onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (this->mouseDown)
  {
    this->mouseDown = false;
    this->loadTextureFromFile("../res/buttons/button.png");
  }
}

void Button::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  this->setText("You clicked!");
}

void Button::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  if (this->isInBoundaries(mouseMoveEvent.x, mouseMoveEvent.y))
  {
    if (!this->mouseIn)
    {
      this->mouseIn = true;
      this->loadTextureFromFile("../res/buttons/buttonHover.png");
    }
  }
  else if (this->mouseIn)
  {
    this->mouseIn = false;
    if (!this->mouseDown)
      this->loadTextureFromFile("../res/buttons/button.png");
  }
}

void Button::setText(std::string str)
{
  this->text.setString(str);
  this->adjustTextPosition();
}

void Button::setColor(sf::Color color)
{
  sprite.setColor(color);
}

void Button::onLock()
{
  setColor(sf::Color(150, 50, 50, 100));
}

void Button::onUnLock()
{
  setColor(sf::Color::White);
}

