//
// Created by Troja on 09/04/2024.
//

#ifndef SUDOKUSOLVER_TEXTBOX_H
#define SUDOKUSOLVER_TEXTBOX_H


#include "objects/Object.h"

class TextBox : public Object
{
private:
    static sf::Font getFont();

    //Size is easier handled through scale so scale it is
    float scale;
    sf::Vector2f position;
    sf::Vector2f size;

    //Text + gridBorder
    sf::Text text, mark;
    sf::RectangleShape box;
    bool highlighted;
    bool marks[9];

    //Initializers
    void initText();
    void initBox();
    static void setTextPosition(sf::Text &txt, float posX, float posY);
public:
    TextBox();
    ~TextBox() override;

    //Universal TextBox font, separate method to get the font for possible load file error
    //Temporary, will move elsewhere in the future
    static sf::Font font;

    void render(sf::RenderTarget *target) override;
    void update() override;

    void setText(std::string txt);
    void setString(sf::String str);
    void setPosition(float posX, float posY);
    void setSize(float boxSize);
    void setBackgroundColor(sf::Color c);
    void setMark(int digit, bool isSet);
    void deleteMarks();

    //Collision detection
    bool isInBoundaries(float posX, float posY) override;

    //Highlight texBox
    void setHighlight(bool isHighlighted);
    void setHighlight();

    //Mouse hover event
    void onMouseMove(sf::Event::MouseMoveEvent mouseMoveEvent) override;

    int getNumberFromText();
};


#endif //SUDOKUSOLVER_TEXTBOX_H
