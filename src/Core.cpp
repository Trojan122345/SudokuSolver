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
  auto *numberGrid = new NumberGrid(50, 50);
  objects.push_back(numberGrid);

  auto *button = new Button(50+31*9+1+50, 75);
  objects.push_back(button);
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
        switch (this->sfmlEvent.key.code)
        {
          case sf::Keyboard::Escape:
            this->window->close();
            break;
          default:
            for (auto &obj: this->objects)
            {
              obj->keyPressed(sfmlEvent.key.code);
            }
            break;
        }
        break;
      case sf::Event::MouseButtonPressed:
        for (auto &obj: this->objects)
        {
          if (obj->isInBoundaries(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y))
            obj->onMousePressed(sfmlEvent.mouseButton);
        }
        break;
      case sf::Event::MouseButtonReleased:
        if (this->sfmlEvent.mouseButton.button == sf::Mouse::Left)
          for (auto &obj: this->objects)
          {
            obj->onMouseReleased(sfmlEvent.mouseButton);
            if (obj->isInBoundaries(sfmlEvent.mouseButton.x, sfmlEvent.mouseButton.y))
              obj->onClick(sfmlEvent.mouseButton);
          }
        break;
      case sf::Event::TextEntered:
        for (auto &obj: this->objects)
        {
          obj->textEntered(sfmlEvent.text.unicode);
        }
        break;
      case sf::Event::MouseMoved:
        for (auto &obj: this->objects)
        {
          obj->onMouseMove(sfmlEvent.mouseMove);
        }
        break;
      default:
        break;
    }
  }
}
