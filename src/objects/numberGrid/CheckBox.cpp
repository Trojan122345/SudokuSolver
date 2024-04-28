//
// Created by Troja on 20/04/2024.
//

#include "objects/numberGrid/CheckBox.h"

CheckBox::CheckBox() : TextBox(), checked(false)
{
  initCheckMark();
}

void CheckBox::render(sf::RenderTarget* target)
{
  TextBox::render(target);
  target->draw(checkMark);
}

void CheckBox::initCheckMark()
{
  checkMark.setFont(*getFont(SEGOEUIEMOJI));
  checkMark.setFillColor(sf::Color::Black);
  checkMark.setCharacterSize(20);

  setCheckMarkPosition();
}

void CheckBox::setText(const std::string &txt)
{
  this->text.setString(txt);
  setTextPosition();
}

void CheckBox::setString(const sf::String &str)
{
  this->text.setString(str);
  setTextPosition();
}

void CheckBox::setPosition(float posX, float posY)
{
  this->position.x = posX;
  this->position.y = posY;
  this->box.setPosition(posX, posY);
  setTextPosition();
  setCheckMarkPosition();
}

void CheckBox::setTextPosition()
{
  text.setOrigin(0, text.getLocalBounds().height / 2);
  text.setPosition(position.x + size.x + 10, position.y + size.y / 2);
}

void CheckBox::setCheckMarkPosition()
{
  wchar_t checkMarkSymbol = 0x2713;
  checkMark.setString(checkMarkSymbol);
  checkMark.setOrigin(checkMark.getLocalBounds().width / 2, checkMark.getLocalBounds().height / 2);
  checkMark.setPosition(position.x + size.x / 2, position.y + size.y / 2 - 5);
  checkMark.setString("");
}


bool CheckBox::isChecked() const
{
  return checked;
}

void CheckBox::setChecked(bool check)
{
  checked = check;
  if (checked)
  {
    wchar_t checkMarkSymbol = 0x2713;
    checkMark.setString(checkMarkSymbol);
  }
  else
    checkMark.setString("");
}

void CheckBox::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  setChecked(!checked);
}
