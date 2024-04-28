//
// Created by Troja on 21/04/2024.
//

#include "SolverGUI.h"
#include "NumberGrid.h"
#include "GridButtons.h"
#include "NumericUpDown.h"

SolverGUI::SolverGUI() : lockGUI(new bool), objects()
{
  initObjects();
}

SolverGUI::~SolverGUI()
{
  for (auto* obj: objects)
  {
    delete obj;
  }
  delete lockGUI;
}

void SolverGUI::render(sf::RenderTarget* target)
{
  for (auto* obj: objects)
  {
    obj->render(target);
  }
}

void SolverGUI::update()
{
  for (auto* obj: objects)
  {
    obj->update();
  }
}

void SolverGUI::initObjects()
{
  *lockGUI = false;

  auto* numberGrid = new NumberGrid(50, 50);
  numberGrid->setLock(lockGUI);
  objects.push_back(numberGrid);

  auto* solverButton = new SolverButton(50 + 31 * 9 + 1 + 50, 75, numberGrid);
  solverButton->setLock(lockGUI);
  objects.push_back(solverButton);

  auto* eraseButton = new EraseButton(50 + 31 * 9 + 1 + 50, 150, numberGrid);
  eraseButton->setLock(lockGUI);
  objects.push_back(eraseButton);

  auto* prefillButton = new PrefillButton(50 + 31 * 9 + 1 + 50, 225, numberGrid);
  prefillButton->setLock(lockGUI);
  objects.push_back(prefillButton);

  auto* solverButtonBrute = new SolveBruteButton(50 + 31 * 9 + 1 + 50 + 200, 75, numberGrid);
  solverButtonBrute->setLock(lockGUI);
  objects.push_back(solverButtonBrute);

  auto* stopButton = new StopButton(50 + 31 * 9 + 1 + 50 + 200 + 200, 75, numberGrid);
  stopButton->setLock(lockGUI);
  objects.push_back(stopButton);

  auto* goSlowBox = new CheckBox();
  goSlowBox->setPosition(50 + 31 * 9 + 1 + 250, 165);
  goSlowBox->setString("Solve slowly");
  goSlowBox->setLock(lockGUI);
  objects.push_back(goSlowBox);

  auto* nud = new NumericUpDown("xyz");
  nud->setPosition(50 + 31 * 9 + 1 + 50 + 200, 225);
  nud->setLabel("Prefill ID");
  nud->setLimits(1, 5);
  prefillButton->addNumeric(nud);
  objects.push_back(nud);

  solverButtonBrute->addGoSlowCheckbox(goSlowBox);
  solverButton->addGoSlowCheckbox(goSlowBox);
}

bool SolverGUI::isInBoundaries(float posX, float posY)
{
  return true;
}

void SolverGUI::onClick(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  for (auto* obj: objects)
  {
    if (obj->isInBoundaries(mouseButtonEvent.x, mouseButtonEvent.y))
      obj->onClick(mouseButtonEvent);
  }
}

void SolverGUI::onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent)
{
  for (auto* obj: objects)
  {
    obj->onMouseMove(mouseMoveEvent);
  }
}

void SolverGUI::onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  for (auto* obj: objects)
  {
    obj->onMousePressed(mouseButtonEvent);
  }
}

void SolverGUI::onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent)
{
  for (auto* obj: objects)
  {
    obj->onMouseReleased(mouseButtonEvent);
  }
}

void SolverGUI::textEntered(const sf::String &str)
{
  for (auto* obj: objects)
  {
    obj->textEntered(str);
  }
}

void SolverGUI::keyPressed(sf::Keyboard::Key key)
{
  for (auto* obj: objects)
  {
    obj->keyPressed(key);
  }
}

void SolverGUI::onLock()
{

}

void SolverGUI::onUnLock()
{

}
