//
// Created by Troja on 21/04/2024.
//

#ifndef SUDOKUSOLVER_GRIDBUTTONS_H
#define SUDOKUSOLVER_GRIDBUTTONS_H

#include "Button.h"
#include "NumericUpDown.h"


class SolverButton : public Button
{
private:
    CheckBox* goSlow;
protected:
    NumberGrid* numberGrid;
    static sf::Text resultText;
    static void initResultText();

    bool pauseSolver, solverDone, solving;

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
    ~EraseButton() override;

    void update() override;
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
};

class PrefillButton : public Button
{
private:
    NumberGrid* numberGrid;
    NumericUpDown* nud;
public:
    explicit PrefillButton(float posX, float posY, NumberGrid* ng);
    ~PrefillButton() override;

    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent) override;

    void setLock(bool* lock) override;
    void addNumeric(NumericUpDown* numericUpDown);
};

class SolveBruteButton : public SolverButton{
public:
    SolveBruteButton(float posX, float posY, NumberGrid* ng);

    void solve() override;
    //void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
};

class StopButton : public Button{
private:
    bool* stop;
public:
    explicit StopButton(float posX, float posY, NumberGrid* ng);
    ~StopButton() override;

    void update() override;
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;

protected:
    void onLock() override;
    void onUnLock() override;
};




#endif //SUDOKUSOLVER_GRIDBUTTONS_H
