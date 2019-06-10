/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#pragma once

#include <vector>
#include <memory>

#include "Window.hpp"

class MenuElement {
public:
	MenuElement(const vector3df &position, std::string type);
	~MenuElement();
	vector3df getPosition() const;
	std::string getType() const;

protected:
	const vector3df position;

private:
	std::string type;
};