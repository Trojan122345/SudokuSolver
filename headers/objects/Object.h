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
public:
    Object();
    virtual ~Object();

    virtual void render(sf::RenderTarget *target)= 0;
    virtual void update() = 0;

    virtual bool isInBoundaries(float posX, float posY) = 0;

    virtual void click(sf::Event::MouseButtonEvent mouseButtonEvent){};

    [[nodiscard]] int getID() const;
    bool compare(Object* object) const;
};


#endif //SUDOKUSOLVER_OBJECT_H
