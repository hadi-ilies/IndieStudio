/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** ButtonElement
*/

#pragma once

#include "UserInterface/MenuElement.hpp"
#include "UserInterface/Button.hpp"

class ButtonElement : public MenuElement {
	public:
		ButtonElement(Window *window, const vector3df &position, const std::string &name);
	    ~ButtonElement();
        Button *getButton() const;
	private:
       Button *button;
};
