/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ButtonElement
*/

#include "ButtonElement.hpp"

ButtonElement::ButtonElement(Window *window, const vector3df &position, const std::string &name)
 : MenuElement(window, position, "Button"), button(new Button(window, position, name))
{
}

ButtonElement::~ButtonElement() = default;