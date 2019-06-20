/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @copyright © 2019, OOP_indie_studio_2018, Zappy group
 * @package UI Package
 * @file MenuElement
 */

#pragma once

#include <vector>
#include <memory>

#include "Window.hpp"

class MenuElement {
public:
	MenuElement(const vector3df &position, std::string type);
	virtual ~MenuElement();
	vector3df getPosition() const;
	std::string getType() const;

protected:
	const vector3df position;

private:
	std::string type;
};