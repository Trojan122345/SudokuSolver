//
// Created by Troja on 09/04/2024.
//

#include <iostream>
#include "Core.h"

Core::Core() :
        videoMode(1600, 900),
        sfmlEvent()
{
  initWindow();
  initVariables();
}

Core::~Core()
{
  for (auto &obj: objects)
  {
    delete obj;
  }
}


void Core::initWindow()
{
  this->window = new sf::RenderWindow(this->videoMode, "Test title", sf::Style::Close | sf::Style::Titlebar);
  this->window->setFramerateLimit(60);
}

void Core::initVariables()
{
  numberGrid = new NumberGrid();
  objects.push_back(numberGrid);
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
  for (Object *object: this->objects)
  {
    object->update();
  }
}

void Core::render()
{
  this->window->clear(sf::Color::White);

  for (Object *object: this->objects)
  {
    object->render(this->window);
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
        if (this->sfmlEvent.key.code == sf::Keyboard::Delete || this->sfmlEvent.key.code == sf::Keyboard::BackSpace)
          this->numberGrid->textErased();
        break;
      case sf::Event::MouseButtonPressed:
        if (this->sfmlEvent.mouseButton.button == sf::Mouse::Left)
          for (auto &obj: this->objects)
          {
            obj->click(sfmlEvent.mouseButton);
          }
        break;
      case sf::Event::TextEntered:
        this->numberGrid->textEntered(sfmlEvent.text.unicode);
        break;
      default:
        break;
    }
  }
}
