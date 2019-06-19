/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
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