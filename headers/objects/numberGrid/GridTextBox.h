//
// Created by Troja on 20/04/2024.
//

#ifndef SUDOKUSOLVER_GRIDTEXTBOX_H
#define SUDOKUSOLVER_GRIDTEXTBOX_H


#include "TextBox.h"
#include "Cell.h"

class GridTextBox : public TextBox
{
private:
    sf::Text mark;
    bool marks[9];
    bool originalDigit;

    bool* solving;

    Cell* cell;

    void setMarkPosition(int digit);
    void initMarkText();
    void deleteMarks();
public:
    GridTextBox();

    void render(sf::RenderTarget* target) override;
    void update() override;

    void setMark(int digit, bool isSet);

    void setOriginalDigit(bool isOriginal);

    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;

    void empty();

    void setCell(Cell* cellToSet);
    void setSolving(bool* solvingToSet);

    void fillCell(bool doMarks);
};


#endif //SUDOKUSOLVER_GRIDTEXTBOX_H
