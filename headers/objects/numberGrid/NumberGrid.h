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
    sf::RectangleShape gridBorder;
    sf::Vector2f position;
    std::vector<std::vector<TextBox*>> cells;

    //initializers
    void initBorder(float posX, float posY);
    void initGrid();

    //Highlight related stuff
    TextBox *highlightedBox;
    void highlightBox(TextBox* box);

    //Key methods
    void textErased();
    void movePressed(sf::Keyboard::Key keyPressed);
public:
    explicit NumberGrid(float posX, float posY);
    ~NumberGrid() override;
    void render(sf::RenderTarget *target) override;
    void update() override;

    //Collision check
    bool isInBoundaries(float posX, float posY) override;

    //Mouse events
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;

    //Text methods
    void textEntered(const sf::String &str) override;
    void keyPressed(sf::Keyboard::Key key) override;
    void setText(const std::string& str, int cellRow, int cellCol);

    //Get finalNumber matrix for the solver
    int** getNumbers();
    std::vector<std::vector<TextBox*>> getCells(){return cells;}
    void deleteAllText();
};


#endif //SUDOKUSOLVER_NUMBERGRID_H
