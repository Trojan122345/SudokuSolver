//
// Created by Troja on 11/04/2024.
//

#ifndef SUDOKUSOLVER_BUTTON_H
#define SUDOKUSOLVER_BUTTON_H


#include <functional>
#include "Object.h"
#include "NumberGrid.h"
#include "Solver.h"
#include "CheckBox.h"
#include <thread>

class Button : public Object
{
private:
    //SFML graphics
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text text;

    //Temp - will move into base object class in the future
    sf::Vector2f position, size;

    //Initializers
    void loadTextureFromFile(std::string filename);
    void initSprite(float posX, float posY, float sizeX, float sizeY);
    void initButton(float posX, float posY);
    void initText();

    void adjustTextPosition();
protected:
    void onLock() override;
    void onUnLock() override;
public:
    Button();
    Button(float posX, float posY);
    ~Button() override;

    void render(sf::RenderTarget* target) override;
    void update() override;

    //Collision check
    bool isInBoundaries(float posX, float posY) override;

    //Mouse methods
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;
    void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent) override;

    void setText(std::string str);
    void setColor(sf::Color color);
};

#endif //SUDOKUSOLVER_BUTTON_H
