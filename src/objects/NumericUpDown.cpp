//
// Created by Troja on 26/04/2024.
//

#include "NumericUpDown.h"

NumericUpDown::NumericUpDown(std::string label) : TextBox(), btnUp(0, 0, 46, 43), btnDown(0, 0, 46, 43)
{
  initLabel(label);
  initButtons();
  value = 0;
  updateText();
  upperLimit = 0;
  lowerLimit = 0;
}

void NumericUpDown::initLabel(std::string &label)
{
  lbl.setCharacterSize(20);
  lbl.setFillColor(sf::Color::Black);
  lbl.setFont(fontArial);
  this->lbl.setString(label);
}

void NumericUpDown::initButtons()
{
  btnUp.setTextures("../res/Buttons/btnUp.png", "../res/Buttons/btnUpHover.png", "../res/Buttons/btnUpClick.png");
  btnUp.setScale(0.6f, 0.35f);
  btnUp.setOrigin(0, 0);
  btnUp.setPosition(this->position.x + 40, this->position.y);

  btnDown.setTextures("../res/Buttons/btnDown.png", "../res/Buttons/btnDownHover.png", "../res/Buttons/btnDownClick.png");
  btnDown.setScale(0.6f, 0.35f);
  btnDown.setOrigin(0, btnDown.getLocalBounds().height);
  btnDown.setPosition(this->position.x + 40, this->position.y + this->size.y);
}

void NumericUpDown::render(sf::RenderTarget* target)
{
  TextBox::render(target);
  target->draw(lbl);
  btnUp.render(target);
  btnDown.render(target);
}

void NumericUpDown::updateText()
{
  setText(std::to_string(value));
}

void NumericUpDown::setPosition(float posX, float posY)
{
  TextBox::setPosition(posX, posY);
  updateLblPosition();
  btnUp.setPosition(this->position.x + 40, this->position.y);
  btnDown.setPosition(this->position.x + 40, this->position.y + this->size.y);
}

void NumericUpDown::updateLblPosition()
{
  this->lbl.setOrigin(0, lbl.getLocalBounds().height / 2);
  this->lbl.setPosition(position.x + 75, position.y + size.y/2 - 5);
}

void NumericUpDown::checkLimits()
{
  if (upperLimit > lowerLimit)
  {
    if (value > upperLimit)
      value = upperLimit;
    else if (value < lowerLimit)
      value = lowerLimit;
  }
}

void NumericUpDown::setLabel(const std::string& label)
{
  this->lbl.setString(label);
  updateLblPosition();
}

void NumericUpDown::setLimits(int lower, int upper)
{
  lowerLimit = lower;
  upperLimit = upper;
  checkLimits();
  updateText();
}

int NumericUpDown::getValue() const
{
  return value;
}

bool NumericUpDown::isInBoundaries(float posX, float posY)
{
  return TextBox::isInBoundaries(posX, posY) || btnUp.isInBoundaries(posX, posY) || btnDown.isInBoundaries(posX, posY);
}

void NumericUpDown::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  btnUp.onMouseMove(mouseMoveEvent);
  btnDown.onMouseMove(mouseMoveEvent);
}

void NumericUpDown::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (btnUp.isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y))
  {
    value++;
  }
  if (btnDown.isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y))
  {
    value--;
  }
  checkLimits();
  updateText();
}

void NumericUpDown::onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  btnUp.onMousePressed(mouseButtonEvent);
  btnDown.onMousePressed(mouseButtonEvent);
}

void NumericUpDown::onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  btnUp.onMouseReleased(mouseButtonEvent);
  btnDown.onMouseReleased(mouseButtonEvent);
}








