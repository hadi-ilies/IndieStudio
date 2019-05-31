/*
** EPITECH PROJECT, 2019
** Button
** File description:
** Button
*/

#include "Error.hpp"
#include "UserInterface/Button.hpp"

Button::Button(Window *window, vector3du &position)
    : position (position), button(window ? window->addCube("Resources/Button/Texture.png") : NULL) //may i have to add types
{
    if (window) {
        const vector3df floatPosition(position.X, position.Y, position.Z);

        if (!button)
            throw Error("button can not be created");
        button->setPosition(floatPosition);
    }
}


Button::~Button()
{
}

ISceneNode *Button::getButton() const
{
    return button;
}

vector3du Button::getPositon() const
{
    return position;
}
