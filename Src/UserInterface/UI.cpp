/*
** EPITECH PROJECT, 2019
** OOP_indie_studio_2018
** File description:
** UserInterface
*/

#include <list>
#include <memory>
#include "UserInterface/UI.hpp"

/**
 * todo ask corentin unique ptr == move 
 * */

UI::UI(Window *window, Menu *mainMenu)
    : window(window)
{
    std::vector<Menu*> menu;
    menu.push_back(mainMenu);
    uiGraph.push_back(menu);
}

UI::~UI()
{
}

void UI::addMenu(uint index, Menu *menu)
{
    uiGraph[index].push_back(menu);
}

std::vector<Menu *> UI::getMenu(const uint &index) const
{
    return uiGraph[index];
}

std::vector<std::vector<Menu *>> UI::getUiGraph() const
{
    return uiGraph;
}

