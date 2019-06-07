/*
** EPITECH PROJECT, 2019
** Wheel
** File description:
** Wheel
*/

#pragma once

#include <memory>
#include <vector>
#include "UserInterface/Button.hpp"
#include "UserInterface/MenuElement.hpp"
#include "Window.hpp"

class Wheel : public MenuElement {
public:
    struct ParamButton {
        std::string name;
        std::string model;
        std::string texture;
    };
public:
	Wheel(Window *window, const vector3df &position, const float &radius, const std::vector<Wheel::ParamButton> &buttons);
	~Wheel();
public :
    enum Dir {RIGHT = 1, LEFT = -1};
public:
    void turnButtons(const Dir &direction, const f32 &timestamps);
    Button *getButton(const uint &buttonIndex) const;
    const vector3df getPosButton(const uint &buttonIndex);
    Button *getCurrentButton() const;
private:
    const float radius;
    uint currentButton;
    std::vector<Button *> buttonList;
};