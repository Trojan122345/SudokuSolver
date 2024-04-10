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
#include "objects/Object.h"
#include "objects/numberGrid/NumberGrid.h"
#include "objects/numberGrid/TextBox.h"

class Core
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event sfmlEvent;
    std::vector<Object *> objects;

    NumberGrid *numberGrid;

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
