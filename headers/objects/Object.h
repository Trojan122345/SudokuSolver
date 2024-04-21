//
// Created by Troja on 09/04/2024.
//

#ifndef SUDOKUSOLVER_OBJECT_H
#define SUDOKUSOLVER_OBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Object
{
private:
    static int NextID;
    int ID;
    int getNextID();

    bool didLock;
protected:
    bool mouseIn, mouseDown;
    bool* locked;

    virtual void onLock() = 0;
    virtual void onUnLock() = 0;
public:
    Object();
    virtual ~Object();

    virtual void render(sf::RenderTarget *target)= 0;
    virtual void update();

    virtual bool isInBoundaries(float posX, float posY) = 0;

    virtual void onClick(sf::Event::MouseButtonEvent mouseButtonEvent){};
    virtual void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent){};
    virtual void onMousePressed(sf::Event::MouseButtonEvent mouseButtonEvent){};
    virtual void onMouseReleased(sf::Event::MouseButtonEvent mouseButtonEvent){};
    virtual void textEntered(const sf::String &str){};
    virtual void keyPressed(sf::Keyboard::Key){};

    virtual void setLock(bool *lock);

    [[nodiscard]] int getID() const;
    bool compare(Object* object) const;
};


#endif //SUDOKUSOLVER_OBJECT_H
