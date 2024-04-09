//
// Created by Troja on 09/04/2024.
//

#ifndef SUDOKUSOLVER_NUMBERGRID_H
#define SUDOKUSOLVER_NUMBERGRID_H


#include "objects/Object.h"
#include "TextBox.h"

class NumberGrid : public Object
{
private:
    sf::RectangleShape box;
    void initBox(float posX, float posY);

    //temporary textmox
    TextBox tbox;
    bool isHighlighted;
public:
    NumberGrid();
    ~NumberGrid() override;
    void render(sf::RenderTarget *target) override;
    void update() override;

    //Collision check
    bool isInBoundaries(float posX, float posY) override;

    //Click
    void click(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void textEntered(const sf::String& str);
};


#endif //SUDOKUSOLVER_NUMBERGRID_H
