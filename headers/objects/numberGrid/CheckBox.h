//
// Created by Troja on 20/04/2024.
//

#ifndef SUDOKUSOLVER_CHECKBOX_H
#define SUDOKUSOLVER_CHECKBOX_H


#include "TextBox.h"

class CheckBox : public TextBox
{
private:
    bool checked;
    sf::Text checkMark;

    void initCheckMark();
protected:
    void setTextPosition() override;
    void setCheckMarkPosition();
public:
    CheckBox();

    void render(sf::RenderTarget* target) override;

    void setText(const std::string &txt) override;
    void setString(const sf::String &str) override;
    void setPosition(float posX, float posY) override;

    bool isChecked() const;
    void setChecked(bool checked);

private:
    void onClick(sf::Event::MouseButtonEvent mouseButtonEvent) override;
};


#endif //SUDOKUSOLVER_CHECKBOX_H
