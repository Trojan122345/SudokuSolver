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
    explicit Object(int id);
    virtual ~Object();
    virtual void render(sf::RenderTarget *target)= 0;
    virtual void update() = 0;
    [[nodiscard]] int getID() const;
    bool compate(Object* object) const;
};


#endif //SUDOKUSOLVER_OBJECT_H
