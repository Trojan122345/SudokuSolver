//
// Created by Troja on 21/04/2024.
//

#ifndef SUDOKUSOLVER_GRIDBUTTONS_H
#define SUDOKUSOLVER_GRIDBUTTONS_H

#include "Button.h"


class SolverButton : public Button
{
private:
    CheckBox* goSlow;
    NumberGrid* numberGrid;
protected:
    static sf::Text resultText;
    static void initResultText();

    bool pauseSolver, solverDone, solving;
    Solver solver;

    void setSlow();
    void resetInitResultText();
    void onLock() override;
    void onUnLock() override;
public:
    explicit SolverButton(float posX, float posY, NumberGrid* ng);
    void render(sf::RenderTarget* target) override;
    void update() override;

    ~SolverButton() override;
    virtual void solve();
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;

    void addGoSlowCheckbox(CheckBox* checkBox);
};

class EraseButton : public Button
{
private:
    NumberGrid* numberGrid;
public:
    explicit EraseButton(float posX, float posY, NumberGrid* ng);
    void update() override;

    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    ~EraseButton() override;
};

class TestButton : public Button
{
private:
    NumberGrid* numberGrid;
    TextBox textBox;
    bool tBoxHighlighted;
public:
    explicit TestButton(float posX, float posY, NumberGrid* ng);
    ~TestButton() override;

    void render(sf::RenderTarget* target) override;
    void update() override;

    void textEntered(const sf::String &str) override;
    void keyPressed(sf::Keyboard::Key key) override;
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void setLock(bool* lock) override;
};

class SolveBruteButton : public SolverButton{
public:
    SolveBruteButton(float posX, float posY, NumberGrid* ng);

    void solve() override;
    //void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
};




#endif //SUDOKUSOLVER_GRIDBUTTONS_H
