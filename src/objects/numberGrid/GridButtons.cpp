//
// Created by Troja on 21/04/2024.
//

#include "GridButtons.h"
#include <regex>

//Solver button
sf::Text SolverButton::resultText = sf::Text();

void SolverButton::initResultText()
{
  SolverButton::resultText.setFont(TextBox::fontArial);
  SolverButton::resultText.setFillColor(sf::Color::Black);
  SolverButton::resultText.setCharacterSize(25);
  SolverButton::resultText.setPosition(250, 20);
}

void SolverButton::resetInitResultText()
{
  SolverButton::resultText.setString("");
}

SolverButton::SolverButton(float posX, float posY, NumberGrid* ng) : Button(posX, posY), solver(), goSlow(nullptr)
{
  pauseSolver = false;
  solverDone = false;
  solving = false;
  this->numberGrid = ng;
  solver.addTextBoxes(this->numberGrid->getCells());
  this->setText("Solve");
  SolverButton::initResultText();
}

SolverButton::~SolverButton()
{

}

void SolverButton::solve()
{
  solver.setSleep(false);
  solver.empty();
  solver.loadNumbers(true);
  setSlow();
  solver.solve(pauseSolver, solverDone);
}

void SolverButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (!solving)
  {
    if (locked == nullptr || !*locked)
    {
      resetInitResultText();
      std::thread{&SolverButton::solve, this}.detach();
      solving = true;
      if (locked != nullptr)
      {
        *locked = true;
      }
      this->setText("Pause");
    }
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
  Button::update();
  if (solverDone)
  {
    solving = false;
    *locked = false;
    pauseSolver = false;
    this->setText("Solve");
    solverDone = false;
    if (!solver.checkConflicts())
      resultText.setString("Success!");
    else
      resultText.setString("Failed!");
  }
}

void SolverButton::addGoSlowCheckbox(CheckBox* checkBox)
{
  goSlow = checkBox;
}

void SolverButton::setSlow()
{
  if (goSlow != nullptr)
    solver.setSleep(goSlow->isChecked());
  else
    solver.setSleep(false);
}

void SolverButton::onLock()
{
  if (!solving)
    Button::onLock();
}

void SolverButton::onUnLock()
{
  Button::onUnLock();
}


//Erase button
EraseButton::EraseButton(float posX, float posY, NumberGrid* ng) : Button(posX, posY)
{
  this->numberGrid = ng;
  this->setText("Delete all");
}

void EraseButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (locked == nullptr || !*locked)
    numberGrid->deleteAllText();
}

EraseButton::~EraseButton()
{

}

void EraseButton::update()
{
  Button::update();
  /*if(locked){
    setColor(sf::Color(150, 50, 50, 100));
  }else
    setColor(sf::Color::White);*/
}


//Test button
TestButton::TestButton(float posX, float posY, NumberGrid* ng) : Button(posX, posY)
{
  numberGrid = ng;
  this->setText("Prefill grid");
  this->textBox.setPosition(posX + 200, posY);
}

TestButton::~TestButton()
{

}

void TestButton::render(sf::RenderTarget* target)
{
  Button::render(target);
  textBox.render(target);
}

void TestButton::update()
{
  Button::update();
  textBox.update();
}

void TestButton::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (locked == nullptr || !*locked)
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
}

void TestButton::textEntered(const sf::String &str)
{
  if (locked == nullptr || !*locked)
  {
    std::string s = str.toAnsiString();
    std::regex reg("[1-9]");
    if (tBoxHighlighted && std::regex_match(s, reg))
      this->textBox.setString(str);
  }
}

void TestButton::onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  if (locked == nullptr || !*locked)
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
}

void TestButton::keyPressed(sf::Keyboard::Key key)
{
  if (tBoxHighlighted && key == sf::Keyboard::BackSpace || key == sf::Keyboard::Delete)
  {
    textBox.setText("");
  }
}

void TestButton::setLock(bool* lock)
{
  Object::setLock(lock);
  textBox.setLock(lock);
}


//Solver brute force button
SolveBruteButton::SolveBruteButton(float posX, float posY, NumberGrid* ng) : SolverButton(posX, posY, ng)
{
  setText("Solve Brute");
}

void SolveBruteButton::solve()
{
  solver.setSleep(false);
  solver.empty();
  solver.loadNumbers(false);
  setSlow();
  solver.solveBrute(pauseSolver, solverDone);
}

