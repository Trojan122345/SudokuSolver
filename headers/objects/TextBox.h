//
// Created by Troja on 09/04/2024.
//

#ifndef SUDOKUSOLVER_TEXTBOX_H
#define SUDOKUSOLVER_TEXTBOX_H


#include "Object.h"
#include "enums.h"

class TextBox : public Object
{
private:

    //Size is easier handled through scale so scale it is
    float scale;

    bool highlighted;

    //Initializers
    void initText();
    void initBox();
protected:
    void onLock() override;
    void onUnLock() override;

    //Text + gridBorder
    sf::RectangleShape box;
    sf::Text text;

    sf::Vector2f position;

    sf::Vector2f size;

    virtual void setTextPosition();
public:
    TextBox();
    ~TextBox() override;

    //Universal TextBox fontArial, separate method to get the fontArial for possible load file error
    //Temporary, will move elsewhere in the future
    static sf::Font fontArial;
    static sf::Font* getFont(FontType fontType);

    void render(sf::RenderTarget* target) override;
    void update() override;


    virtual void setText(const std::string& txt);
    virtual void setString(const sf::String& str);
    virtual void setPosition(float posX, float posY);
    void setSize(float boxSize);
    void setBackgroundColor(sf::Color c);

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
