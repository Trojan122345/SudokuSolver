//
// Created by Troja on 11/04/2024.
//

#include "objects/Button.h"

Button::Button()
{
  initButton(0, 0, 150, 50);
  initText();
}

Button::Button(float posX, float posY, float sizeX, float sizeY)
{
  initButton(posX, posY, sizeX, sizeY);
  initText();
}

Button::~Button()
{

}

void Button::initTextures(const std::string &tex, const std::string &texHover, const std::string &texClick)
{
  texture.loadFromFile(tex);
  textureHover.loadFromFile(texHover);
  textureClick.loadFromFile(texClick);
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

void Button::initButton(float posX, float posY, float sizeX, float sizeY)
{
  initTextures("../res/buttons/button.png", "../res/buttons/buttonHover.png", "../res/buttons/buttonClick.png");
  this->initSprite(posX, posY, sizeX, sizeY);
  this->origin.x = 0;
  this->origin.y = 0;
  this->scale.x = 1;
  this->scale.y = 1;
}

void Button::initText()
{
  this->text.setFont(TextBox::fontArial);
  this->text.setCharacterSize(20);
  this->text.setFillColor(sf::Color::Black);

  adjustTextPosition();
}

void Button::adjustTextPosition()
{
  this->text.setOrigin(origin.x / scale.x + this->text.getLocalBounds().width / 2,
                       origin.y / scale.y + this->text.getLocalBounds().height / 2);
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

void Button::setTextures(const std::string &tex, const std::string &texHover, const std::string &texClick)
{
  initTextures(tex, texHover, texClick);
  sprite.setTextureRect(sf::IntRect(position.x, position.y, texture.getSize().x, texture.getSize().y));
}

void Button::setTextures(const std::string &tex)
{
  setTextures(tex, tex, tex);
}

bool Button::isInBoundaries(float posX, float posY)
{
  return posX >= this->position.x - origin.x && posX <= this->position.x + this->size.x - origin.x &&
         posY >= this->position.y - origin.y && posY <= this->position.y + this->size.y - origin.y;
}

void Button::onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (this->isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y) && !this->mouseDown)
  {
    this->mouseDown = true;
    this->sprite.setTexture(textureClick);
  }
}

void Button::onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (this->mouseDown)
  {
    this->mouseDown = false;
    this->sprite.setTexture(texture);
  }
}

void Button::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{

}

void Button::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  if (this->isInBoundaries(mouseMoveEvent.x, mouseMoveEvent.y))
  {
    if (!this->mouseIn)
    {
      this->mouseIn = true;
      this->sprite.setTexture(textureHover);
    }
  }
  else if (this->mouseIn)
  {
    this->mouseIn = false;
    if (!this->mouseDown)
      this->sprite.setTexture(texture);
  }
}

void Button::setText(const std::string &str)
{
  this->text.setString(str);
  this->adjustTextPosition();
}

void Button::setColor(sf::Color color)
{
  sprite.setColor(color);
}

void Button::setScale(float scaleX, float scaleY)
{
  sprite.setScale(scaleX, scaleY);
  this->size.x *= scaleX;
  this->size.y *= scaleY;
  this->scale.x = scaleX;
  this->scale.y = scaleY;
}

void Button::setOrigin(float x, float y)
{
  this->origin.x = x * scale.x;
  this->origin.y = y * scale.y;
  this->sprite.setOrigin(x, y);
  adjustTextPosition();
}

void Button::setPosition(float x, float y)
{
  position.x = x;
  position.y = y;
  sprite.setPosition(position);
}

sf::FloatRect Button::getLocalBounds()
{
  return sprite.getLocalBounds();
}

void Button::onLock()
{
  setColor(sf::Color(150, 50, 50, 100));
}

void Button::onUnLock()
{
  setColor(sf::Color::White);
}

