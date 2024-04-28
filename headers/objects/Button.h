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
    sf::Texture textureHover;
    sf::Texture textureClick;
    sf::Sprite sprite;
    sf::Text text;

    //Temp - will move into base object class in the future
    sf::Vector2f position, size, origin, scale;

    //Initializers
    void initTextures(const std::string &tex, const std::string &texHover, const std::string &texClick);
    void initSprite(float posX, float posY, float sizeX, float sizeY);
    void initButton(float posX, float posY, float sizeX, float sizeY);
    void initText();

    void adjustTextPosition();
protected:
    void onLock() override;
    void onUnLock() override;
public:
    Button();
    Button(float posX, float posY, float sizeX, float sizeY);
    ~Button() override;

    void render(sf::RenderTarget* target) override;
    void update() override;

    void setTextures(const std::string &tex, const std::string &texHover, const std::string &texClick);
    void setTextures(const std::string &tex);

    //Collision check
    bool isInBoundaries(float posX, float posY) override;

    //Mouse methods
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent) override;
    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;
    void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent) override;

    void setText(const std::string& str);
    void setColor(sf::Color color);
    void setSize(float sizeX, float sizeY);
    void setScale(float scaleX, float scaleY);
    void setOrigin(float x, float y);
    void setPosition(float x, float y);
    sf::FloatRect getLocalBounds();
};

#endif //SUDOKUSOLVER_BUTTON_H
