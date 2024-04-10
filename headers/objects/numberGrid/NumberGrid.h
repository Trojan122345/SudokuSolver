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
    //Graphic objects
    sf::RectangleShape border;
    sf::Vector2f position;
    std::vector<std::vector<TextBox>> boxes;

    //First box ID - for arrow movement
    int firstBoxID;

    //initializers
    void initBorder(float posX, float posY);
    void initGrid();

    //Highlight related stuff
    TextBox *highlightedBox;
    void highlightBox(int row, int col);

public:
    NumberGrid();
    ~NumberGrid() override;
    void render(sf::RenderTarget *target) override;
    void update() override;

    //Collision check
    bool isInBoundaries(float posX, float posY) override;

    //Click method
    void click(sf::Event::MouseButtonEvent mouseButtonEvent) override;

    //Text methods
    void textEntered(const sf::String &str);
    void textErased();
    void movePressed(sf::Keyboard::Key keyPressed);
};


#endif //SUDOKUSOLVER_NUMBERGRID_H
