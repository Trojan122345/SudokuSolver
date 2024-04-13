//
// Created by Troja on 11/04/2024.
//

#include <iostream>
#include "objects/numberGrid/Button.h"
#include "objects/numberGrid/TextBox.h"

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
  this->text.setFont(TextBox::font);
  this->text.setCharacterSize(20);
  this->text.setString("Click me!");
  this->text.setFillColor(sf::Color::Black);

  adjustTextPosition();
}

void Button::adjustTextPosition()
{
  this->text.setOrigin(this->text.getLocalBounds().width/2, this->text.getLocalBounds().height/2);
  this->text.setPosition(this->position.x + this->size.x/2, this->position.y + this->size.y/2);
}

void Button::render(sf::RenderTarget *target)
{
  target->draw(sprite);
  target->draw(text);
}

void Button::update()
{

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

//Solver button
SolverButton::SolverButton(float posX, float posY, NumberGrid *ng) : Button(posX, posY), solver()
{
  this->numberGrid = ng;
  solver.addTextBoxes(this->numberGrid->getCells());
  this->setText("solve");
}

SolverButton::~SolverButton()
{

}

void SolverButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  solver.loadNumbers();
  std::cout<<"\n";
  solver.solve();
  solver.empty();
}

//Erase button
EraseButton::EraseButton(float posX, float posY, NumberGrid *ng) : Button(posX, posY)
{
  this->numberGrid = ng;
  this->setText("Delete all");
}

void EraseButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  numberGrid->deleteAllText();
  numberGrid->setText("1", 0, 0);
  numberGrid->setText("8", 1, 0);
  numberGrid->setText("4", 3, 0);
  numberGrid->setText("5", 3, 1);
  numberGrid->setText("9", 5, 1);
  numberGrid->setText("2", 5, 2);
  numberGrid->setText("7", 7, 1);
  numberGrid->setText("6", 7, 2);
  numberGrid->setText("4", 8, 2);
  numberGrid->setText("3", 0, 3);
  numberGrid->setText("8", 0, 6);
  numberGrid->setText("1", 1, 5);
  numberGrid->setText("4", 1, 6);
  numberGrid->setText("7", 1, 7);
  numberGrid->setText("2", 2, 3);
  numberGrid->setText("5", 2, 4);
  numberGrid->setText("2", 3, 6);
  numberGrid->setText("8", 3, 7);
  numberGrid->setText("3", 4, 4);
  numberGrid->setText("6", 5, 7);
  numberGrid->setText("7", 5, 8);
  numberGrid->setText("6", 6, 4);
  numberGrid->setText("5", 6, 5);
  numberGrid->setText("4", 7, 3);
  numberGrid->setText("8", 7, 8);
  numberGrid->setText("3", 8, 5);
  numberGrid->setText("6", 8, 6);
  numberGrid->setText("9", 8, 8);
  numberGrid->setText("9", 0, 2);
}

EraseButton::~EraseButton()
{

}

//Erase button
