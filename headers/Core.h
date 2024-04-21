//
// Created by Troja on 09/04/2024.
//

#ifndef SUDOKUSOLVER_CORE_H
#define SUDOKUSOLVER_CORE_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Object.h"
#include "NumberGrid.h"
#include "TextBox.h"
#include "GridButtons.h"

class Core
{
private:
    //SFML graphics
    sf::VideoMode videoMode;
    sf::RenderWindow* window;
    sf::Event sfmlEvent;

    //My objects
    std::vector<Object*> objects;

    //Init methods
    void initWindow();
    void initVariables();
public:
    Core();
    ~Core();

    void startLoop();

    void render();
    void update();

    [[nodiscard]]bool running() const;
    void pollEvents();
};


#endif //SUDOKUSOLVER_CORE_H
