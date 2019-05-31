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
	Menu(Window *window, const uint &nbButton); //window in param
	~Menu();
    void addButton();
    void deleteButton(uint index);


private:
    Window *window;
    std::vector<std::unique_ptr<Button>> buttonList;
};

