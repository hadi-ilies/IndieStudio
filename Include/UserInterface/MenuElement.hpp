/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#pragma once

#include <vector>
#include <list>
#include <memory>
#include "Window.hpp"

class MenuElement {
public:
	MenuElement(Window *window, const vector3df &position, const std::string &type);
	~MenuElement();
	vector3df getPosition() const;
	std::string getType() const;
protected:
        Window *window;
	const vector3df position;
private:
	std::string type;
};