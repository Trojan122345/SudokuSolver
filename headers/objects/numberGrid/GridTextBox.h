//
// Created by Troja on 20/04/2024.
//

#ifndef SUDOKUSOLVER_GRIDTEXTBOX_H
#define SUDOKUSOLVER_GRIDTEXTBOX_H


#include "TextBox.h"

class GridTextBox : public TextBox
{
private:
    sf::Text mark;
    bool marks[9];
    bool originalDigit;

    void setMarkPosition(int digit);
protected:
    void initMarkText();
public:
    GridTextBox();

    void render(sf::RenderTarget* target) override;

    void setMark(int digit, bool isSet);
    void deleteMarks();

    void setOriginalDigit(bool isOriginal);

    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;

    void empty();
};


#endif //SUDOKUSOLVER_GRIDTEXTBOX_H
