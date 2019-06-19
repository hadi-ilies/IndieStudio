/**
 * @author Corentin Gautier (https://github.com/Adorr29)
 * @author Hadi Bereksi (https://github.com/hadi-ilies)
 * @author Camille Police (https://github.com/CamillePolice)
 * @date © 2019, Zappy group
 * @package UI Package
 * @file Wheel (scroll menu)
 */

#pragma once

#include <memory>
#include <vector>

#include "UserInterface/AButton.hpp"
#include <UserInterface/Button.hpp>
#include "UserInterface/MenuElement.hpp"
#include "UserInterface/FontButton.hpp"
#include "Window.hpp"

class Wheel : public MenuElement {
public:
    struct ParamButton {
        std::string name;
        std::string model;
        std::string texture;
    };
    enum Dir {
        BASE = 0,
        RIGHT = -1,
        LEFT = 1
    };

public:
    Wheel(Window &_window, const vector3df &position, const float &radius, const std::vector<std::string> &buttonsNames, IrrFontBuffer &irrFontBuffer);
    Wheel(Window &_window, const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons);
    ~Wheel() override;

public:
    void turnButtons(const Dir &direction, const f32 &timestamps);
    AButton *getButton(const uint &buttonIndex) const;
    const vector3df getPosButton(const uint &buttonIndex);
    AButton *getCurrentButton() const;

private:
    const float radius;
    uint currentButton;
    uint displayedButton;
    std::vector<AButton *> buttonList;
};
