/*
** EPITECH PROJECT, 2019
** wheel
** File description:
** Wheel
*/

#include "UserInterface/Wheel.hpp"

#include <iostream>
//vector struct

Wheel::Wheel(Window *window, const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons)
    : MenuElement(window, position, "Wheel"), radius(radius), currentButton(0)
{
    std::cout << "Position :" << position.X << "  " << position.Y << "  " << position.Z << std::endl;
    for (uint i = 0; i < buttons.size(); i++) {
        vector3df pos = getPosButton(i);
        std::cout << "WIWI" << std::endl;
        buttonList.push_back(new Button(window, pos, buttons[i].name, buttons[i].model, buttons[i].texture));
    }
}

Wheel::~Wheel()
{
}

const vector3df Wheel::getPosButton(const uint &buttonIndex)
{
    return vector3df(radius * cos(2 * buttonIndex * M_PI / buttonList.size()) + position.X, position.Y, radius * sin(2 * buttonIndex * M_PI / buttonList.size() + position.Z));
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