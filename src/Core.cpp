//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include "Core.h"

Core::Core() :
        videoMode(1600, 900),
        sfmlEvent(),
        window(new sf::RenderWindow(this->videoMode, "Test title", sf::Style::Close | sf::Style::Titlebar))
{
  initWindow();
  initVariables();
}

Core::~Core()
{
  for (auto &backgroundObject: backgroundObjects)
  {
    delete backgroundObject;
  }
  for (auto &movindObject: movingObjects)
  {
    delete movindObject;
  }
}


void Core::initWindow()
{
  this->window->setFramerateLimit(60);
}

void Core::initVariables()
{
  numberBox = new NumberGrid();
  backgroundObjects.push_back(numberBox);
}

void Core::startLoop()
{
  while (running())
  {
    update();
    render();
  }
}

void Core::update()
{
  this->pollEvents();
  for (Object *object: this->backgroundObjects)
  {
    object->update();
  }
  if (!movingObjects.empty())
  {
    for (Object *object: this->movingObjects)
    {
      object->update();
    }
  }
}

void Core::render()
{
  this->window->clear(sf::Color::White);

  for (Object *object: this->backgroundObjects)
  {
    object->render(this->window);
  }
  if (!movingObjects.empty())
  {
    for (Object *object: this->movingObjects)
    {
      object->render(this->window);
    }
  }

  this->window->display();
}

bool Core::running() const
{
  return this->window->isOpen();
}

void Core::pollEvents()
{
  while (this->window->pollEvent(sfmlEvent))
  {
    switch (this->sfmlEvent.type)
    {
      case sf::Event::Closed:
        this->window->close();
      case sf::Event::KeyPressed:
        if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
          this->window->close();
        break;
      case sf::Event::MouseButtonPressed:
        if (this->sfmlEvent.mouseButton.button == sf::Mouse::Left)
          if (this->numberBox->isInBoundaries(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y))
            this->numberBox->click(sfmlEvent.mouseButton);
        break;
      case sf::Event::TextEntered:
          numberBox->textEntered(sfmlEvent.text.unicode);
        break;
      default:
        break;
    }
  }
}
