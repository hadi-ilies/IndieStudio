/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include <list>
#include <memory>
#include "UserInterface/UI.hpp"

UI::UI(Window *window, Menu *mainMenu)
    : window(window)
{
    std::list<unique_ptr<Menu>> menu;
    //menu.push_back(std::unique_ptr<Menu>(mainMenu));
    //uiGraph.push_back(menu);
}

UI::~UI()
{
}