//
// Created by Troja on 09/04/2024.
//

#ifndef SUDOKUSOLVER_NUMBERGRID_H
#define SUDOKUSOLVER_NUMBERGRID_H


#include "Object.h"
#include "GridTextBox.h"
#include "Solver.h"

class NumberGrid : public Object
{
private:
    //Graphic objects
    sf::RectangleShape gridBorder;
    sf::Vector2f position;
    std::vector<std::vector<GridTextBox*>> cells;

    //Sudoku solver
    Solver solver;
    bool* solving;
    bool* stop;
    bool sleep;

    //initializers
    void initBorder(float posX, float posY);
    void initGrid();
    void connectCells();

    //Highlight related stuff
    TextBox* highlightedBox;
    void highlightBox(TextBox* box);

    //Key methods
    void textErased();
    void movePressed(sf::Keyboard::Key keyPressed);
protected:
    void onLock() override;
    void onUnLock() override;
public:
    explicit NumberGrid(float posX, float posY);
    ~NumberGrid() override;
    void render(sf::RenderTarget* target) override;
    void update() override;

    //Collision check
    bool isInBoundaries(float posX, float posY) override;

    //Mouse events
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;

    //Text methods
    void textEntered(const sf::String &str) override;
    void keyPressed(sf::Keyboard::Key key) override;
    void setText(const std::string &str, int cellRow, int cellCol);

    void deleteAllText();

    void solveSetup(bool doMarks);
    void solve(bool &pause, bool &done);
    void solveBrute(bool &pause, bool &done);
    bool checkSolvedPuzzle();

    void setSleep(bool doSleep);
    void fillCells(bool doMarks);
    void setSolvingPtr(bool* solvingToSet);
    bool* getStopPtr();
};


#endif //SUDOKUSOLVER_NUMBERGRID_H
