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
public:
	Menu(Window *window, const uint &nbButton, const std::string &type); //window in param
	~Menu();
    void addButton(Window *window, vector3du &position);
    void turnButtons(const vector3df &pos, const float &timestamp);
    void deleteButton(const uint index);

private:
    Window *window;
    std::vector<std::unique_ptr<Button>> buttonList;
};

