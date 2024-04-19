//
// Created by Troja on 11/04/2024.
//

#include <iostream>
#include <thread>
#include <regex>
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
SolverButton::SolverButton(float posX, float posY, NumberGrid* ng) : Button(posX, posY), solver()
{
  pauseSolver = false;
  solverDone = false;
  solving = false;
  this->numberGrid = ng;
  solver.addTextBoxes(this->numberGrid->getCells());
  this->setText("Solve");
  resultText.setFont(TextBox::font);
  resultText.setFillColor(sf::Color::Black);
  resultText.setCharacterSize(25);
  resultText.setPosition(250, 20);
}

SolverButton::~SolverButton()
{

}

void SolverButton::solve()
{
  solver.empty();
  solver.loadNumbers();
  solver.solve(pauseSolver, solverDone);
}

void SolverButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (!solving)
  {
    std::thread{&SolverButton::solve, this}.detach();
    solving = true;
    this->setText("Pause");
  }
  else if (solving && !pauseSolver)
  {
    pauseSolver = true;
    this->setText("Resume");
  }
  else if (solving && pauseSolver)
  {
    pauseSolver = false;
    this->setText("Pause");
  }
}

void SolverButton::render(sf::RenderTarget* target)
{
  Button::render(target);
  target->draw(resultText);
}

void SolverButton::update()
{
  if (solverDone)
  {
    solving = false;
    pauseSolver = false;
    this->setText("Solve");
    solverDone = false;
    if (!solver.checkConflicts())
      resultText.setString("Success!");
    else
      resultText.setString("Failed!");
  }
}

//Erase button
EraseButton::EraseButton(float posX, float posY, NumberGrid* ng) : Button(posX, posY)
{
  this->numberGrid = ng;
  this->setText("Delete all");
}

void EraseButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  numberGrid->deleteAllText();
}

EraseButton::~EraseButton()
{

}

//Test button
TestButton::TestButton(float posX, float posY, NumberGrid* ng) : Button(posX, posY)
{
  numberGrid = ng;
  this->setText("Test fill");
  this->textBox.setPosition(posX + 200, posY);
}

void TestButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  numberGrid->deleteAllText();
  switch (textBox.getNumberFromText())
  {
    case 2:
      numberGrid->setText("7", 0, 0);
      numberGrid->setText("4", 0, 2);
      numberGrid->setText("1", 0, 6);
      numberGrid->setText("2", 1, 3);
      numberGrid->setText("3", 1, 6);
      numberGrid->setText("9", 1, 8);
      numberGrid->setText("5", 2, 1);
      numberGrid->setText("1", 2, 4);
      numberGrid->setText("6", 2, 5);
      numberGrid->setText("2", 2, 8);
      numberGrid->setText("8", 3, 0);
      numberGrid->setText("7", 3, 1);
      numberGrid->setText("2", 3, 2);
      numberGrid->setText("9", 3, 4);
      numberGrid->setText("5", 5, 4);
      numberGrid->setText("9", 5, 6);
      numberGrid->setText("1", 5, 7);
      numberGrid->setText("8", 5, 8);
      numberGrid->setText("5", 6, 0);
      numberGrid->setText("4", 6, 3);
      numberGrid->setText("8", 6, 4);
      numberGrid->setText("2", 6, 7);
      numberGrid->setText("2", 7, 0);
      numberGrid->setText("7", 7, 2);
      numberGrid->setText("9", 7, 5);
      numberGrid->setText("3", 8, 2);
      numberGrid->setText("4", 8, 6);
      numberGrid->setText("5", 8, 8);
      break;
    case 1:
      numberGrid->setText("4", 0, 2);
      numberGrid->setText("5", 1, 0);
      numberGrid->setText("3", 1, 5);
      numberGrid->setText("6", 1, 6);
      numberGrid->setText("6", 2, 0);
      numberGrid->setText("3", 2, 1);
      numberGrid->setText("2", 2, 2);
      numberGrid->setText("4", 2, 3);
      numberGrid->setText("1", 2, 4);
      numberGrid->setText("8", 2, 5);
      numberGrid->setText("9", 3, 0);
      numberGrid->setText("7", 3, 2);
      numberGrid->setText("2", 3, 4);
      numberGrid->setText("4", 3, 5);
      numberGrid->setText("3", 3, 8);
      numberGrid->setText("4", 4, 1);
      numberGrid->setText("1", 4, 2);
      numberGrid->setText("6", 4, 3);
      numberGrid->setText("7", 4, 5);
      numberGrid->setText("2", 4, 6);
      numberGrid->setText("9", 4, 7);
      numberGrid->setText("2", 5, 0);
      numberGrid->setText("9", 5, 3);
      numberGrid->setText("3", 5, 4);
      numberGrid->setText("4", 5, 6);
      numberGrid->setText("1", 5, 8);
      numberGrid->setText("3", 6, 3);
      numberGrid->setText("6", 6, 4);
      numberGrid->setText("1", 6, 5);
      numberGrid->setText("5", 6, 6);
      numberGrid->setText("2", 6, 7);
      numberGrid->setText("7", 6, 8);
      numberGrid->setText("3", 7, 2);
      numberGrid->setText("7", 7, 3);
      numberGrid->setText("8", 7, 8);
      numberGrid->setText("1", 8, 6);
      break;
    case 3:
      numberGrid->setText("4", 0, 2);
      numberGrid->setText("2", 0, 7);
      numberGrid->setText("9", 0, 8);
      numberGrid->setText("6", 1, 2);
      numberGrid->setText("1", 1, 3);
      numberGrid->setText("7", 1, 8);
      numberGrid->setText("7", 2, 1);
      numberGrid->setText("2", 2, 2);
      numberGrid->setText("9", 2, 4);
      numberGrid->setText("3", 2, 5);
      numberGrid->setText("8", 3, 1);
      numberGrid->setText("9", 3, 2);
      numberGrid->setText("3", 3, 8);
      numberGrid->setText("2", 4, 4);
      numberGrid->setText("6", 5, 0);
      numberGrid->setText("5", 5, 6);
      numberGrid->setText("4", 5, 7);
      numberGrid->setText("9", 6, 3);
      numberGrid->setText("3", 6, 4);
      numberGrid->setText("8", 6, 6);
      numberGrid->setText("1", 6, 7);
      numberGrid->setText("1", 7, 0);
      numberGrid->setText("4", 7, 5);
      numberGrid->setText("9", 7, 6);
      numberGrid->setText("7", 8, 0);
      numberGrid->setText("9", 8, 1);
      numberGrid->setText("4", 8, 6);
      break;
    case 4:
      numberGrid->setText("5", 0, 3);
      numberGrid->setText("2", 0, 6);
      numberGrid->setText("7", 0, 7);
      numberGrid->setText("8", 1, 4);
      numberGrid->setText("7", 1, 5);
      numberGrid->setText("9", 1, 8);
      numberGrid->setText("8", 2, 6);
      numberGrid->setText("4", 2, 8);
      numberGrid->setText("2", 3, 3);
      numberGrid->setText("4", 3, 7);
      numberGrid->setText("7", 4, 0);
      numberGrid->setText("1", 4, 2);
      numberGrid->setText("5", 4, 6);
      numberGrid->setText("3", 4, 8);
      numberGrid->setText("9", 5, 1);
      numberGrid->setText("1", 5, 5);
      numberGrid->setText("8", 6, 0);
      numberGrid->setText("9", 6, 2);
      numberGrid->setText("1", 7, 0);
      numberGrid->setText("6", 7, 3);
      numberGrid->setText("7", 7, 4);
      numberGrid->setText("4", 8, 1);
      numberGrid->setText("7", 8, 2);
      numberGrid->setText("2", 8, 5);
      break;
    case 5:
    default:
      numberGrid->setText("6", 0, 1);
      numberGrid->setText("3", 0, 4);
      numberGrid->setText("9", 0, 8);
      numberGrid->setText("7", 1, 0);
      numberGrid->setText("3", 1, 1);
      numberGrid->setText("5", 1, 7);
      numberGrid->setText("1", 1, 8);
      numberGrid->setText("5", 2, 0);
      numberGrid->setText("8", 2, 5);
      numberGrid->setText("1", 3, 0);
      numberGrid->setText("6", 3, 4);
      numberGrid->setText("2", 3, 5);
      numberGrid->setText("9", 4, 2);
      numberGrid->setText("7", 4, 6);
      numberGrid->setText("9", 5, 3);
      numberGrid->setText("7", 5, 4);
      numberGrid->setText("5", 5, 8);
      numberGrid->setText("3", 6, 3);
      numberGrid->setText("4", 6, 8);
      numberGrid->setText("4", 7, 0);
      numberGrid->setText("1", 7, 1);
      numberGrid->setText("7", 7, 7);
      numberGrid->setText("6", 7, 8);
      numberGrid->setText("8", 8, 0);
      numberGrid->setText("5", 8, 4);
      numberGrid->setText("1", 8, 7);
      break;
  }
}

TestButton::~TestButton()
{

}

void TestButton::render(sf::RenderTarget* target)
{
  Button::render(target);
  textBox.render(target);
}

void TestButton::textEntered(const sf::String &str)
{
  std::string s = str.toAnsiString();
  std::regex reg("[1-9]");
  if (tBoxHighlighted && std::regex_match(s, reg))
    this->textBox.setString(str);
}

void TestButton::onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  Button::onMouseReleased(mouseButtonEvent);
  if (textBox.isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y))
  {
    tBoxHighlighted = !tBoxHighlighted;
    textBox.setHighlight(tBoxHighlighted);
  }
  else
  {
    tBoxHighlighted = false;
    textBox.setHighlight(tBoxHighlighted);
  }
}

void TestButton::keyPressed(sf::Keyboard::Key key)
{
  if (tBoxHighlighted && key == sf::Keyboard::BackSpace || key == sf::Keyboard::Delete)
  {
    textBox.setText("");
  }
}
