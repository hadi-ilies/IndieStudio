/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @package UI Package
 * @file ButtonElement
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

