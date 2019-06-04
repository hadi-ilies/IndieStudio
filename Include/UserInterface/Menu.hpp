/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#pragma once

#include <memory>
#include <vector>
#include "UserInterface/Button.hpp"
#include "Window.hpp"

class Menu {
public :
    enum Dir {RIGHT = 1, LEFT = -1};
public:
	Menu(Window *window, const uint &nbButton, const std::string &type); //window in param
	~Menu();
    void addButton(Window *window, vector3du &position);
    void turnButtons(const Dir &direction, const f32 &timestamps);
    Button *getButton(const uint &buttonIndex) const;
    const vector3df getPosButton(const uint &buttonIndex);
    Button *getCurrentButton() const;
    void deleteButton(const uint index);
private:
    Window *window;
    const float radius;
    uint currentButton;
    std::vector<Button *> buttonList;
};

