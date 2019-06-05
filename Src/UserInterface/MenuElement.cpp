/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include <list>
#include <memory>
#include "UserInterface/MenuElement.hpp"

MenuElement::MenuElement(Window *window, const vector3df &position, const std::string &type)
    : window(window), position(position), type(type)
{
}

MenuElement::~MenuElement()
{

}

vector3df MenuElement::getPosition() const
{
    return position;
}

std::string MenuElement::getType() const
{
    return type;
}

