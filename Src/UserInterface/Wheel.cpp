/*
** EPITECH PROJECT, 2019
** wheel
** File description:
** Wheel
*/

#include "UserInterface/Wheel.hpp"

#include <iostream>

Wheel::Wheel(Window *window, const vector3df &position, const float &radius, const std::vector<std::string> &buttons)
    : MenuElement(window, position, "Wheel"), radius(radius), currentButton(0)
{
        std::cout << "Position :" << position.X << "  " << position.Y << "  " << position.Z << std::endl;
    for (uint i = 0; i < buttons.size(); i++) {
        vector3df pos = getPosButton(i);
        pos.X += position.X; pos.Y += position.Y; pos.Z += position.Z;
        buttonList.push_back(new Button(window, pos, buttons[i]));
    }
}

Wheel::~Wheel()
{
}

const vector3df Wheel::getPosButton(const uint &buttonIndex)
{
    std::cout << "Position :" << position.Y << std::endl;
    return vector3df(radius * cos(2 * buttonIndex * M_PI / buttonList.size()), position.Y, radius * sin(2 * buttonIndex * M_PI / buttonList.size()));
}

void Wheel::turnButtons(const Wheel::Dir &direction, const f32 &timestamps)
{
    if (buttonList[0]->animHasFinished()) {
        for (uint i = 0; i < buttonList.size(); i++)
            buttonList[i]->animation(window, getPosButton((i + currentButton + buttonList.size() + direction) % buttonList.size()), timestamps);
        currentButton = (currentButton + buttonList.size() + direction) % buttonList.size();
    }
}

Button *Wheel::getButton(const uint &buttonIndex) const
{
    return buttonList[buttonIndex];
}

Button *Wheel::getCurrentButton() const
{
    return buttonList[currentButton];
}