//
// Created by Troja on 21/04/2024.
//

#ifndef SUDOKUSOLVER_SOLVERGUI_H
#define SUDOKUSOLVER_SOLVERGUI_H


#include "Object.h"

class SolverGUI : public Object
{
private:
    bool *lockGUI;
    std::vector<Object*> objects;

    void initObjects();
public:
    SolverGUI();
    ~SolverGUI() override;
    void render(sf::RenderTarget* target) override;
    void update() override;
    bool isInBoundaries(float posX, float posY) override;
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;
    void onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void textEntered(const sf::String &str) override;
    void keyPressed(sf::Keyboard::Key key) override;
protected:
    void onLock() override;
    void onUnLock() override;
};


#endif //SUDOKUSOLVER_SOLVERGUI_H
