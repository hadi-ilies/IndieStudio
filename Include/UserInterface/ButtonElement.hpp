/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ButtonElement.hpp
*/

#pragma once

#include "UserInterface/MenuElement.hpp"
#include "UserInterface/AButton.hpp"
#include "UserInterface/Button.hpp"

class ButtonElement : public MenuElement {
public:
    ButtonElement(Window &_window, const vector3df &position, const std::string &name, const std::string &model, const std::string &texture);
    ~ButtonElement();
    AButton *getButton() const;

private:
    AButton *button;
};

