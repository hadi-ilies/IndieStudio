/*
** EPITECH PROJECT, 2019
** Menu
** File description:
** Menu
*/

#include "UserInterface/Menu.hpp"

Menu::Menu(Window *window, const uint &nbButton) // may have to add type that will change the repartion of buttons
    : window(window)
{
    for (uint i = 0; i < nbButton; i++) {
        vector3du pos(1, 1 ,1);
        buttonList.push_back(unique_ptr<Button>(new Button(window, pos)));
    }
}

Menu::~Menu()
{
}

void Menu::addButton(Window *window, vector3du &position)
{
    buttonList.push_back(unique_ptr<Button>(new Button(window, position)));
}

void Menu::deleteButton(const uint index)
{
    buttonList.erase(buttonList.begin() + index);
}
