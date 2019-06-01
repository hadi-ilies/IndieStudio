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
	void linkMenu(Menu menu1, Menu menu2);
	void loop(); //code into it
        void addMenu();

private:
        Window *window;
        std::vector<std::list<std::unique_ptr<Menu>>> uiGraph; // i will need doubly linked list
};