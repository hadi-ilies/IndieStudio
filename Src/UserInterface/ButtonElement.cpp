/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ButtonElement
*/

#include "UserInterface/ButtonElement.hpp"
#include "UserInterface/Button.hpp"

ButtonElement::ButtonElement(Window *window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture)
 : MenuElement(window, position, "Button"), button(new Button(window, position, name, model, texture))
{
}

ButtonElement::~ButtonElement() = default;

Button *ButtonElement::getButton() const
{
    return button;
}