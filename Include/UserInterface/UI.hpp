/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#pragma once

#include <vector>
#include <list>
#include <memory>
#include "Window.hpp"
#include "UserInterface/Menu.hpp"

/** todo
 * I need to create an undirected graph of menu
 * and continue archi
 * */

class UI {
public:
	UI(Window *window, Menu *mainMenu);
	~UI();
	void linkMenu();
        void addMenu(uint index, Menu *menu);
	std::vector<Menu *> getMenu(const uint &index) const;
	std::vector<std::vector<Menu *>> getUiGraph() const;
private:
        Window *window;
        std::vector<std::vector<Menu *>> uiGraph;
};