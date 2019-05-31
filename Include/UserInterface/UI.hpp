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
#include "UserInterface/Menu.hpp"

/** todo
 * I need to create an undirected graph of menu
 * and continue archi
 * */

class UI {
public:
	UI(Window *window);
	~UI();
        void addMenu();

private:
        Window *window;
        std::vector<std::unique_ptr<Menu>> menuList;
};