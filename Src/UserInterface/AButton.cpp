/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** AButton
*/

#include "UserInterface/AButton.hpp"

AButton::AButton(Window *window, const vector3df &position, const std::string &name, const std::string &type)
    : window(window), position(position), name(name), anim(NULL), type(type)
{
}

AButton::~AButton()
{
}

const std::string AButton::getName() const
{
    return name;
}

vector3df AButton::getPosition() const
{
    return position;
}

bool AButton::animHasFinished() const
{
    return !anim || anim->hasFinished();
}
