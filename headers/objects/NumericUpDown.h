//
// Created by Troja on 26/04/2024.
//

#ifndef SUDOKUSOLVER_NUMERICUPDOWN_H
#define SUDOKUSOLVER_NUMERICUPDOWN_H


#include "TextBox.h"
#include "Button.h"

class NumericUpDown : public TextBox
{
private:
    sf::Text lbl;
    int value;
    int upperLimit, lowerLimit;

    Button btnUp;
    Button btnDown;

    void initLabel(std::string &label);
    void initButtons();
    void updateText();
public:
    explicit NumericUpDown(std::string label);
    void render(sf::RenderTarget* target) override;

    void setPosition(float posX, float posY) override;
    void updateLblPosition();
    void checkLimits();

    void setLabel(const std::string& lbl);
    void setLimits(int lower, int upper);
    int getValue() const;

    bool isInBoundaries(float posX, float posY) override;

    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent) override;
};


#endif //SUDOKUSOLVER_NUMERICUPDOWN_H
